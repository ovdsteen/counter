'use strict';

var jquery = require('jquery'),
	config = JSON.parse( jquery('[data-env]').html() ),
	socket = require('socket.io-client')('ws://'+config.host+':'+config.socket);

var user = {
	ip: Math.floor((Math.random() * 1000) + 1)
};

socket.on('connect', function(){
	socket.emit('adduser',user);
});

socket.on('update', function(data){
	jquery('.amount').html(data.amount);
});
