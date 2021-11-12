from flask import Flask, jsonify, request
stores = {
    'name': 'Tesco',
    'items': [
        {
            'name': 'Item X',
            'price': 23
        }
    ]
}
app = Flask(__name__)


@app.route("/home")
def home():
    return "<h1>Hello world</h1>"


@app.route("/json")
def json():
    return jsonify({'key': 'value', 'key2': [1, 2, 3]})


@app.route("/store")
def get_store():
    json_file = jsonify({'stores:': stores})
    return json_file


@app.route("/store", methods=['POST'])
def create_store():
    request_data = request.get_json()
    new_store = {'name': request_data['name'], 'items': request_data['items']}
    stores.append(new_store)
    return jsonify(new_store)


app.run(port=5000)
