from enum import unique
from flask import Flask, request, render_template
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager,login_user,current_user, logout_user, login_required, UserMixin
import json
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+mysqlconnector://root:password@localhost/users'
app.config['SECRET_KEY'] = 'secretkey'

db = SQLAlchemy(app)
login_manager = LoginManager()
login_manager.init_app(app)

class User(UserMixin, db.Model):
    __tablename__ = 'user'
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password = db.Column(db.String(80), nullable=False)
    ischef = db.Column(db.String(5), nullable=False)
    transactions = db.relationship('Transaction', backref='user')


class Menu(db.Model):
    __tablename__ = 'menu'
    id = db.Column(db.Integer, primary_key=True)
    halfprice = db.Column(db.Integer)
    fullprice = db.Column(db.Integer)
    orders = db.relationship('Order', backref='menu')

class Transaction(db.Model):
    __tablename__ = 'transaction'
    id = db.Column(db.Integer, primary_key=True)
    userid = db.Column(db.Integer, db.ForeignKey('user.id'))
    tip = db.Column(db.Float(precision=2))
    discount = db.Column(db.Float(precision=2))
    split = db.Column(db.Integer)
    total = db.Column(db.Float(precision=2))
    orders = db.relationship('Order', backref='transaction')


class Order(db.Model):
    __tablename__ = 'order'
    id = db.Column(db.Integer, primary_key=True)
    itemid = db.Column(db.Integer, db.ForeignKey('menu.id'))
    transactionid = db.Column(db.Integer, db.ForeignKey('transaction.id'))
    plate  = db.Column(db.String(5), nullable=False)
    quantity = db.Column(db.Integer)
def notchef():
    return "User is not chef"

@login_manager.user_loader
def load_user(user_id):
    return User.query.get(user_id)

@login_manager.unauthorized_handler
def unauthorized():
    return "User is not logged in."

@app.route('/user/login',methods=['GET'])
def login():
    user_data=request.get_json()
    username = user_data['username']
    password = user_data['password']
    check_user = User.query.filter_by(username=username).first()
    if (check_user is not None):
        if (check_user.password == password):
            login_user(check_user)
            return "Logged in successfully"
        else:
            return "Incorrect Password"
    else:
        return "No such User exists"
@app.route('/user/logout',methods=['GET'])
@login_required
def logout():
    logout_user()
    return "User has been logged out"

@app.route('/menu/add',methods=['POST'])
@login_required
def additem():
    chef_status=current_user.ischef
    if chef_status == "NO":
        return notchef()
    menu_data = request.get_json()
    item_id=menu_data['id']
    full_price=menu_data['full']
    half_price=menu_data['half']
    item = Menu(id=item_id,halfprice=half_price,fullprice=full_price)
    db.session.add(item)
    db.session.commit()
    return "Item added Successfully"

@app.route('/menu/fetch',methods=['GET'])
@login_required
def getmenu():
    menuitems=Menu.query.all()
    for item in menuitems:
        print(item.fullprice," ",item.halfprice)
    return "items fetched"

@app.route('/transaction/entry',methods=['POST'])
@login_required
def performTransaction():
    return "done"

@app.route('/transaction/fetch',methods=['GET'])
@login_required
def fetchTransaction():


if (__name__ == '__main__'):
    #db.create_all()
    app.run(port=8000, debug=True)
