const SENSOR_ID = 1;

const config = require('./config');
const fetch = require('node-fetch');
const Meter = require('./meter');

const meter = new Meter('/dev/ttyACM0');
console.log("init", new Date().toISOString());
const data = meter.get(SENSOR_ID);
let date = new Date();
date.setHours(date.getHours() + 3);
const body = JSON.stringify({
    'controller_mac': config['controller']['mac'],
    'sensor_id': SENSOR_ID,
    'value': data['Value'] * 10,
    'hash': date.toString(),
    'timestamp': date.toISOString().substr(0, 19), // there is a bug in libmbus
});
console.log(JSON.stringify(data))
console.log(body);
fetch(`${config['server']['host']}${config['server']['prefix']}/sensor.addRecord`,
    {
        method: 'POST',
        body: body,
//        headers: { 'Content-Type': 'application/json' },
    })
    .then(res => res.json())
    .then(res => console.log(res))
    .catch(e => console.log(e));

