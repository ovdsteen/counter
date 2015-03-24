'use strict';

var	http = require('http'),
	config = require('./config'),
	server = http.createServer(require('./app')),
	io = require('socket.io').listen(config.socket),
	dgram = require('dgram'),
	client = dgram.createSocket('udp4'),
	output = {},
	users = [];

function FormatNumberLength(num, length) {
	var r = "" + num;
	while (r.length < length) {
		r = "0" + r;
	}
	return r;
}

io.sockets.on('connection', function(socket) {

	socket.on('adduser', function(data) {

		socket.ip = data.ip; // set client ip adres as sockit ID

		var id = data.ip, // id is the clients IP
			index = users.indexOf(id); // check if exist

		if ( index == -1 ){ // put in array if not exist
			users.push( id );
		}

		output.amount = users.length; // amount of active users
		output.users = users; // all users

		// send to arduino
		var v = users.length;
		var message = new Buffer( "000" + v + ":0:0:0" ); //users.length+":101:102"
		client.send( message, 0, message.length, 8888, config.arduinoIp );

		io.emit('update', {
			amount: output.amount
		});

		console.log('data: ',output)

	});

	socket.on('disconnect', function(){

		var id = socket.ip, // which sockit disconnect
			index = users.indexOf(id); // does the sockit exist in array

		if ( index >= 0 ){
			users.splice( index , 1 ); // delete IP from array
		}

		// send to arduino
		var message = new Buffer( "000"+users.length+":0:0:0" ); //users.length+":101:102"
		client.send(message, 0, message.length, 8888, config.arduinoIp)

		io.emit('update', {
			amount: users.length
		});

	});

});
