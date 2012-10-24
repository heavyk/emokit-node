
emokit = require '../build/Release/emokit'

console.log "emokit:", emokit
devices = emokit.init!
console.log "\#devices:", devices

get_data = emokit.connect!
console.log "emokit.data", get_data

if typeof get_data is \function
	for i from 0 til 100
		console.log "data:", get_data!
else
	console.log "could not connect!!!!"
