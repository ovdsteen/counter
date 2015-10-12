'use strict';

var app = require('./app'),
	config = require('./config'),
	request = require('request');

app.get('/', function(req, res){
	res.render('index', {
		host: config.host,
		socket: config.socket
	});
});
