const config = require('./config');
const fetch = require('node-fetch');
let Meter = require('./meter');
const {ArgumentParser} = require('argparse');

const USE_STUBS = process.env['USE_STUBS'];

if (USE_STUBS) {
  Meter = class {
    _value = 100;

    get() {
      return this._value += Math.round(Math.random() * 10);
    }
  };
}

const sendValue = function(sensorId, value) {
  const date = new Date();
  const body = JSON.stringify({
    'controller_mac': config['controller']['mac'],
    'sensor_id': sensorId,
    'value': data['Value'] * 10,
    'hash': date.toString(),
    'timestamp': date.toISOString().substr(0, 19), // there is a bug in libmbus
  });
  return fetch(
      `${config['server']['host']}${config['server']['prefix']}/sensor.addRecord`,
      {
        method: 'POST',
        body: body,
        // headers: { 'Content-Type': 'application/json' },
      });
};

const main = function() {
  const parser = new ArgumentParser({
    description: 'Animated stickers for Telegram (*.tgs) to animated GIFs converter',
  });
  parser.addArgument('--sensor-id', {type: Number, required: true});
  parser.addArgument('--device', {required: true});
  parser.addArgument('--interval', {type: Number, default: 10});

  const args = parser.parseArgs();
  const meter = new Meter(args.device);

  setInterval(() => {
    try {
      const data = meter.get(1); // mbus sensor id = 1
      if (data && data['Value']) {
        console.log(data);
      } else {
        console.error('Can not read value');
      }
    } catch (e) {
      console.error(e);
    }
  }, args.interval * 1000);

};

main();
