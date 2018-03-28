// Run this like:
// node server.js
//
// Make sure you're in the directory containing livegraph.js and the public directory that contains the

var net = require('net');

// dataPort is the TCP port we listen on from the Electron. This value must match the Electron code
var dataPort = 7123;

// Start a TCP Server. This is what receives data from the Particle Electron
// https://gist.github.com/creationix/707146
net.createServer(function (socket) {
	console.log('data connection started from ' + socket.remoteAddress);
	
	// The server sends a 8-bit byte value for each sample. Javascript doesn't really like
	// binary values, so we use setEncoding to read each byte of a data as 2 hex digits instead.
	socket.setEncoding('hex');
	
	socket.on('data', function (data) {
		// We received data on this connection. Send it to all of the SSE clients.
		console.log('data ' + data);

		// Echo it back
		socket.write(data);
	});
	socket.on('end', function () {
		console.log('data connection ended');
	});
}).listen(dataPort);


console.log('listening on port ' + dataPort + ' for data');
