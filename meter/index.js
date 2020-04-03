const sh = require('shelljs');

class Meter {
    constructor(device) {
        this._device = device;
    }

    get(port) {
        const {stdout, stderr, code} = (() => {
            const stub = (() => {
                try {
                    return require('./stub.json');
                } catch (e) {}
            })();
            if (!stub) {
                return sh.exec(`${__dirname}/m4m_controller ${this._device} ${port}`, {silent: true});
            } else {
                return {stdout: JSON.stringify(stub), stderr: '', code: 0};
            }
        })();

        if (code !== 0) throw stderr;
        console.log("STDOUT:", stdout);
        return JSON.parse(stdout)['MBusData']['DataRecords'][0];
    }
}

module.exports = Meter;
