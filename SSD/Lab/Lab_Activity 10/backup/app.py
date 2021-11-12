from enum import unique
from flask import Flask, request, render_template
from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = 'secretKey'

db = SQLAlchemy(app)


class Student(db.Model):
    id = db.Column(db.Integer, primary_key=True, autoincrement=False)
    name = db.Column(db.String(80))
    stream = db.Column(db.String(80))


@app.route('/create', methods=['POST'])
def create():
    if request.method == 'POST':
        request_data = request.get_json()
        id = request_data['id']
        name = request_data['name']
        stream = request_data['stream']
        check = Student.query.filter_by[id == id].first()
        if check is not None:
            return "id already exists."
        else:
            obj = Student('id', 'name', 'stream')
            db.session.add(obj)
            db.session.commit()
            return "new user added."

@app.route('/read', methods=['GET'])
def read():
    if request.method == 'GET':
        request_data = request.get_json()


@app.route('/update', methods=['PUT'])
def update():
    if request.method == 'PUT':
        request_data = request.get_json()


@app.route('/delete', methods=['DELETE'])
def delete():
    if request.method == 'DELETE':
        request_data = request.get_json()


app.run(port=8000, debug=True)
