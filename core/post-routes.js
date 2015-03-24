'use strict';

var app = require('./app');

app.use(function(req, res, next){
	res.status(404).render('error');
});
