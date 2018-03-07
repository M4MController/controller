const SENSOR_ID = 1;

const config = require('./config');
const http = require('http');
const Meter = require('./meter');

const meter = new Meter('/dev/ttyACM0');

const data = meter.get(SENSOR_ID);

const body = JSON.stringify({
    'controller_mac': config['controller']['mac'],
    'sensor_id': SENSOR_ID,
    'value': data['Value'],
    'timestamp': new Date().toISOString().substr(0, 19), // there is a bug in libmbus
});
http.request({
    host: config['server']['host'],
    path: `${config['server']['prefix']}/sensor.addRecord`,
    port: config['server']['port'],
    method: 'POST',
    headers: {
        'Content-Type': 'application/json',
        'Content-Length': body.length
    },
}).write(body);
