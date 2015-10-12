'use strict';

var fs = require('fs');

module.exports = function(grunt){

	require('matchdep').filterDev('grunt-*').forEach(grunt.loadNpmTasks);

	var config = {

		mkdir: {
			all: {
				options: {
					create: ['public/css', 'public/js']
				}
			}
		},

		concurrent: {
			dev: {
				tasks: ['nodemon', 'watch'],
				options: {
					logConcurrentOutput: true
				}
			}
		},

		uglify: {
			dist: {
				files: {
					'public/js/app.js': 'src/js/app.js'
				}
			}
		},

		browserify: {
			base: {
				files: {
					'public/js/app.js': 'src/js/app.js'
				}
			}
		},

		nodemon: {
			dev: {}
		},

		sass: {

		},

		watch: {
			options: {
				nospawn: true,
				livereload: true
			},
			js: {
				files: ['src/js/*.js', 'src/js/**/*.js'],
				tasks: ['browserify']
			},
			views: {
				files: ['views/**/*.html'], // which files to watch
			}
		}
	};


	var readCssDir = function(dir, target){

		if (!fs.existsSync(dir)) return;

		var count = 0, hasSubdirs, filePath,
			name, input, output, globs;

		fs.readdirSync(dir)
		.forEach(function(fileName){

			if (/^_/.test(fileName)) return;

			if (!config.sass[target]){
				config.sass[target] = {files: {}};
			}

			filePath = dir + '/' + fileName;
			if (fs.statSync(filePath).isDirectory()){
				hasSubdirs = true;
				return;
			}

			name = fileName.match(/(.*)\.scss/)[1];
			input = dir + '/' + name + '.scss';
			output = 'public/css/' + name + '.css';
			config.sass[target].files[output] = input;
			count ++;
		});

		if (count > 0){
			globs = [dir + '/*.scss'];
			if (hasSubdirs){
				globs.push(dir + '/**/*.scss');
			}
			config.watch[target] = {
				files: globs,
				tasks: ['sass:' + target]
			};
		}
	};

	readCssDir(__dirname + '/src/sass', 'base');

	grunt.initConfig(config);


	grunt.registerTask('default', [
		'concurrent:dev',
	]);

	grunt.registerTask('build', [
		'mkdir',
		'browserify'
	]);
};
