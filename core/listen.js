'use strict';

var	http = require('http'),
	config = require('./config'),
	server = http.createServer(require('./app'));

server.listen(config.listen,function(){
	console.log("server started on " + config.listen);
});

