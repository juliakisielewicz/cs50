import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]

    owned = (db.execute("SELECT name, symbol, SUM(shares) AS shares FROM transactions WHERE user_id = ? GROUP BY name, symbol", user_id))

    grand_total = 0
    for item in owned:
        item["price"] = (lookup(item["symbol"]))["price"]
        grand_total += item["shares"] * item["price"]

    cash = (db.execute("SELECT * FROM users WHERE id = ?", user_id))[0]['cash']

    grand_total = grand_total + cash

    return render_template("index.html", stocks=owned, cash=cash, grand_total=grand_total)


@app.route("/top_up", methods=["GET", "POST"])
@login_required
def top_up():
    """ Add additional cash to the account """

    if request.method == "POST":

        user_id = session["user_id"]

        try:
            additional = float(request.form.get("cash"))
        except:
            return apology("must provide number")

        if additional <= 0:
            return apology("must provide positive number")

        current = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        db.execute("UPDATE users SET cash = ? WHERE id = ?", current + additional, user_id)

        return redirect("/")

    else:

        return render_template("top_up.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        user_id = session["user_id"]
        symbol = request.form.get("symbol").upper()
        api_data = lookup(symbol)
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("must provide integer")

        if not symbol:
            return apology("must provide symbol")

        if api_data is None:
            return apology("incorrect symbol")

        if shares <= 0:
            return apology("must provide positive integer")


        price = api_data["price"]

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']

        total_price = price * shares

        if cash < total_price:
            return apology("not enough cash available")
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total_price, user_id)

            db.execute("INSERT INTO transactions (user_id, type, symbol, name, shares, price) VALUES (?, ?, ?, ?, ?, ?)", user_id, "buy", symbol, api_data["name"], shares, price)


        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]

    hist = db.execute("SELECT symbol, shares, price, date FROM transactions WHERE user_id = ?", user_id)

    return render_template("history.html", history=hist)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide symbol")

        if lookup(request.form.get("symbol")) is None:
            return apology("incorrect symbol")

        share = lookup(request.form.get("symbol"))

        return render_template("quoted.html", name=share["name"], symbol=share["symbol"], price=share["price"])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        elif not request.form.get("confirmation"):
            return apology("must provide password second time")

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 0:
            return apology("username already exists")

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords don't match")

        hash = generate_password_hash(request.form.get("password"))

        db.execute("INSERT INTO users(username, hash) VALUES (?, ?)", request.form.get("username"), hash)

        return redirect("/login")

    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    owned = (db.execute("SELECT symbol, SUM(shares) AS shares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id))

    if request.method == "POST":

        symbol = request.form.get("symbol")

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("must provide integer")

        if not symbol:
            return apology("must provide symbol")

        if shares <= 0:
            return apology("must provide positive integer")


        for item in owned:

            if item["symbol"] == symbol:
                if shares > item["shares"]:
                    return apology("not enough shares available")


        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']

        price = (lookup(symbol))["price"]

        total_income = price * shares


        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + total_income, user_id)

        db.execute("INSERT INTO transactions (user_id, type, symbol, name, shares, price) VALUES (?, ?, ?, ?, ?, ?)", user_id, "sell", symbol, (lookup(symbol))["name"], -shares, price)

        return redirect("/")

    else:
        return render_template("sell.html", stocks=owned)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
