'use strict';

var $ = require('jquery'),
	socket = require('socket.io-client')('ws://localhost:5000');

var user = {
	ip: Math.floor((Math.random() * 1000) + 1)
};

socket.on('connect', function(){
	socket.emit('adduser',user);
});

socket.on('update', function(data){
	$('.amount').html(data.amount);
});
