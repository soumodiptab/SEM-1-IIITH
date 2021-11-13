from enum import unique
from flask import Flask, request, render_template
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager, login_user, logout_user, login_required, UserMixin


app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///user.db'
app.config['SECRET_KEY'] = 'secretkey'

db = SQLAlchemy(app)
login_manager = LoginManager()
login_manager.init_app(app)


class User(UserMixin, db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password = db.Column(db.String(80), nullable=False)


@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))

@app.route('/signin', methods = ['GET', 'POST'])
def signin():
    return render_template('signin.html')

@app.route('/do_signin', methods = ['GET', 'POST'])
def do_signin():
    if(request.method=='POST'):
        username = request.form['username']
        password = request.form['password']
        check_user = User.query.filter_by(username=username).first()
        if(check_user is not None):
            if(check_user.password == password):
                login_user(check_user)
                return "LOGGED in successfully"
            else:
                return "Incorrect Password"
        else:
            return "No such User exists"

@app.route('/signup', methods = ['GET', 'POST'])
def signup():
    return render_template('signup.html')

@app.route('/do_signup', methods = ['GET', 'POST'])
def do_signup():
    if(request.method=='POST'):
        username = request.form['username']
        password = request.form['password']
        check_user = User.query.filter_by(username=username).first()
        if(check_user is not None):
            return "User already registered, please sign in"
        else:
            user = User(username=username, password=password)
            db.session.add(user)
            db.session.commit()
            return "Registered Successfully"

@app.route('/signout')
@login_required
def signout():
    logout_user()
    return "Sign out successful"


@app.route('/demo/<id>')
def demo(id):
    return "Id is " + id


if(__name__ == '__main__'):
    app.run(port=8000,debug=True)