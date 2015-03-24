'use strict';

var deepMixIn = require('mout/object/deepMixIn'),
	fs = require('fs'), config = {};

deepMixIn(config, require('../config.json'));

if (fs.existsSync(process.cwd() + '/config-local.json')){
	deepMixIn(config, require(process.cwd() + '/config-local.json'));
}

module.exports = config;
