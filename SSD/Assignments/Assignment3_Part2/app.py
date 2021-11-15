from enum import unique
from flask import Flask, request, render_template, jsonify
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager, login_user, current_user, logout_user, login_required, UserMixin
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
    plate = db.Column(db.String(5), nullable=False)
    price = db.Column(db.Integer, nullable=False)
    quantity = db.Column(db.Integer, nullable=False)


def notchef():
    return "User is not chef"


def wrap_json(message):
    return jsonify({'msg': message})


@login_manager.user_loader
def load_user(user_id):
    return User.query.get(user_id)


@login_manager.unauthorized_handler
def unauthorized():
    return wrap_json('User is not logged in')


@app.route('/user/signup', methods=['POST'])
def signup():
    user_data = request.get_json()
    username = user_data['username']
    password = user_data['password']
    check_user = User.query.filter_by(username=username).first()
    if check_user is not None:
        return wrap_json('User already exists')
    user = User(username=username, password=password, ischef='NO')
    db.session.add(user)
    db.session.commit()
    return wrap_json('User added successfully')


@app.route('/user/login', methods=['GET'])
def login():
    user_data = request.get_json()
    username = user_data['username']
    password = user_data['password']
    check_user = User.query.filter_by(username=username).first()
    if check_user is not None:
        if check_user.password == password:
            login_user(check_user)
            if current_user.ischef == 'YES':
                return {'msg': 'Chef has Logged in', 'ischef': True}
            else:
                return {'msg': 'User has Logged in', 'ischef': False}
        else:
            return wrap_json('Incorrect Password')
    else:
        return wrap_json('No such User exists')


@app.route('/user/logout', methods=['GET'])
@login_required
def logout():
    logout_user()
    return wrap_json('User has been logged out')


@app.route('/menu/add', methods=['POST'])
@login_required
def additem():
    chef_status = current_user.ischef
    if chef_status == "NO":
        return notchef()
    menu_data = request.get_json()
    item_id = menu_data['id']
    full_price = menu_data['full']
    half_price = menu_data['half']
    check_item = Menu.query.filter_by(id=item_id).first()
    if check_item is not None:
        return wrap_json('Menu item already exists')
    item = Menu(id=item_id, halfprice=half_price, fullprice=full_price)
    db.session.add(item)
    db.session.commit()
    return wrap_json('Item added Successfully')


@app.route('/menu/fetch', methods=['GET'])
@login_required
def getmenu():
    menuwrapper = {}
    menuitems = Menu.query.all()
    menulist = []
    for item in menuitems:
        itemDict = item.__dict__
        itemDict.pop('_sa_instance_state')
        menulist.append(itemDict)
    menuwrapper = {'items': menulist}
    return jsonify(menuwrapper)


@app.route('/transaction/entry', methods=['POST'])
@login_required
def performTransaction():
    transactionData = request.get_json()
    orders = transactionData['orders']
    userid = current_user.id
    tip = transactionData['tip']
    discount = transactionData['discount']
    split = transactionData['split']
    total = transactionData['total']
    new_transaction = Transaction(userid=userid, tip=tip, discount=discount, split=split, total=total)
    db.session.add(new_transaction)
    db.session.flush()
    transactionid = new_transaction.id
    for order in orders:
        new_order = Order(itemid=order['itemid'], transactionid=transactionid, price=order['price'], plate=order['plate'],quantity=order['quantity'],)
        db.session.add(new_order)
    db.session.commit()
    return wrap_json('Transaction completed')

@app.route('/transaction/all', methods=['GET'])
@login_required
def fetchTransactions():
    userid = current_user.id
    transactionList = Transaction.query.filter_by(userid=userid).order_by(Transaction.id)
    transactions = []
    for t in transactionList:
        tData = t.__dict__
        tData.pop('_sa_instance_state')
        transactions.append(tData)
    twrapper = {'transactions': transactions}
    return jsonify(twrapper)


@app.route('/transaction/fetch', methods=['GET'])
@login_required
def fetchTransaction():
    userid = current_user.id
    tjson = request.get_json()
    transactionid = tjson['id']
    transaction = Transaction.query.filter_by(id=transactionid).first()
    orderList=Order.query.filter_by(transactionid=transactionid).order_by(Order.itemid)
    orders=[]
    for order in orderList:
        orderData = order.__dict__
        orderData.pop('_sa_instance_state')
        orders.append(orderData)
    twrapper=transaction.__dict__
    twrapper.pop('_sa_instance_state')
    twrapper['orders']=orders
    return jsonify(twrapper)

if (__name__ == '__main__'):
    # db.create_all()
    app.run(port=8000, debug=True, use_debugger=False, use_reloader=False, passthrough_errors=True)
