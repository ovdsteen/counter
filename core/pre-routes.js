'use strict';

var config = require('./config');

require('./app')
	.use(require('serve-static')(process.cwd() + '/public'))
	.use(function(req, res, next){
		next();
	});
