const pg = require('pg');

const getClient = async function(uri) {
  const client = new pg.Client(uri);
  await client.connect();
  return client;
};

exports.createSensorIfNotExist = async function(uri) {
  const client = await getClient(uri);

  if (!(await client.query('SELECT id from sensors WHERE id = 3')).rows.length) {
    await client.query(`
INSERT INTO sensors (id, name, controller_id, sensor_type)
VALUES (3, 'Electricity', 1, 1)
  `);
    console.log('Created sensor entity');
  }
};

exports.saveValue = function(uri, value) {
  const client = new pg.Client(uri);
  client.connect();

  const date = new Date();
  client.query(
      'INSERT INTO sensor_data (sensor_id, data) values(3, $1)',
      [
        {
          timestamp: date.toISOString().substr(0, 19),
          value,
        },
      ],
  );
};
