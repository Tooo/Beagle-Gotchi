"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
// var socket = io.connect();
// $(document).ready(function() {
// 	socket.on('commandReply', function(result) {
// 		var newDiv = $('<code></code>')
// 			.text(result)
// 			.wrapInner("<div></div>");
// 		$('#messages').append(newDiv);
// 		$('#messages').scrollTop($('#messages').prop('scrollHeight'));
// 	});
	
// });

// Pass in a 16x16 array to display on pet screen 
function setPetScreen(pixels) {
	let n = pixels.length;
	let m = pixels[0].length;
	let table = document.getElementById('petScreen');

	for (let i=0; i < n; i++) {
		let row = table.insertRow(i);
		for (let j=0; j < m; j++) {
			let col = row.insertCell(j);
			pixels[i][j] === '1' ? col.innerHTML = 'X' : col.innerHTML = ' '; 
		}
	} 
}

// Pass in a list of buttons to be part of the menu
function setMenuItems(menuBtns) {
    let n = menuBtns.length;
    let menuForm = document.getElementById('menuContainer');
    for (let i=0; i < n; i++) {
        menuForm.appendChild(menuBtns[i]);
    }
}

var testScreen = 
[
    [' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' '],
    [' ', ' ', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' '],
    [' ', ' ', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' '],
    [' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' '],
    [' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' '],
    [' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' '],
    [' ', '1', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' '],
    [' ', '1', ' ', '1', '1', ' ', '1', ' ', ' ', '1', '1', ' ', '1', ' ', '1', ' '],
    [' ', '1', ' ', '1', '1', ' ', '1', ' ', ' ', '1', '1', ' ', '1', ' ', '1', ' '],
    [' ', '1', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' '],
    [' ', ' ', '1', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', '1', ' ', ' '],
    [' ', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', '1', ' ', '1', ' ', ' ', ' ', ' ', '1', ' ', '1', ' ', ' ', ' '],
    [' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', '1', ' ', '1', '1', ' ', '1', ' ', ' ', ' ', ' ', ' '],
];

function testSetMenus() {
    let interactButton = document.createElement('button');
    let feedButton = document.createElement('button');
    let gamesButton = document.createElement('button');
    let backButton = document.createElement('button');

    interactButton.innerHTML = 'Interact';
    feedButton.innerHTML = 'Feed';
    gamesButton.innerHTML = 'Games';
    backButton.innerHTML = 'Back';

    interactButton.addEventListener('click', () => {
        console.log("interact");
    });
    feedButton.addEventListener('click', () => {
        console.log("Feed");
    });
    gamesButton.addEventListener('click', () => {
        console.log("Games");
    });
    backButton.addEventListener('click', () => {
        console.log("Back");
    });

    let buttonList = [interactButton, feedButton, gamesButton, backButton];
    setMenuItems(buttonList);
}

setPetScreen(testScreen);
testSetMenus();

// function sendCommandViaUDP(message) {
// 	socket.emit('daUdpCommand', message);
// };