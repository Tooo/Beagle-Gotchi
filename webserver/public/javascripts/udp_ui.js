"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();

// Pet screen stages 
var eggStage =[
    [' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' '],
    [' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' '],
    [' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' '],
    [' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' '],
    [' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' '],
    [' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' '],
    [' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' '],
    [' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' '],
    [' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' '],
    [' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' '],
    [' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' '],
];

var babyStage =[
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' '],
    [' ', ' ', '1', '1', '1', '1', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' ', ' '],
    [' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' '],
    [' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' '],
    [' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' '],
    [' ', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1', ' '],
    [' ', '1', ' ', ' ', '1', ' ', '1', ' ', ' ', ' ', '1', ' ', '1', ' ', '1', ' '],
    [' ', '1', ' ', ' ', '1', ' ', '1', ' ', ' ', ' ', '1', ' ', '1', ' ', '1', ' '],
    [' ', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1', ' '],
    [' ', ' ', '1', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', '1', ' ', ' '],
    [' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
];

var childStage =[
    [' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', ' '],
    [' ', '1', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', ' '],
    [' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' '],
    [' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' '],
    [' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' '],
    [' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' '],
    [' ', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1', ' '],
    [' ', '1', ' ', ' ', '1', ' ', '1', ' ', ' ', ' ', '1', ' ', '1', ' ', '1', ' '],
    [' ', '1', ' ', ' ', '1', ' ', '1', ' ', ' ', ' ', '1', ' ', '1', ' ', '1', ' '],
    [' ', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1', ' '],
    [' ', ' ', '1', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', '1', ' ', ' '],
    [' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' '],
    [' ', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', '1', '1', '1', '1', '1', '1', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' '],
];

var teenStage = [
    [' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', ' ', ' ', ' '],
    [' ', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' ', ' '],
    [' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' '],
    [' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' '],
    [' ', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1', ' '],
    [' ', '1', ' ', ' ', '1', ' ', '1', ' ', ' ', ' ', '1', ' ', '1', ' ', '1', ' '],
    [' ', '1', ' ', ' ', '1', ' ', '1', ' ', ' ', ' ', '1', ' ', '1', ' ', '1', ' '],
    [' ', '1', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1', ' '],
    [' ', ' ', '1', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', '1', ' ', ' '],
    [' ', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', '1', ' ', '1', ' ', ' ', ' ', ' ', '1', ' ', '1', ' ', ' ', ' '],
    [' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', '1', ' ', '1', '1', ' ', '1', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' '],
];

var adultStage =[
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

var petStages = [eggStage, babyStage, childStage, teenStage, adultStage];

// Menu Buttons
var mainMenu = [];
var feedMenu = [];
var interactMenu = [];


$(document).ready(function() {
	// Get all the values for the web page

	// Menu buttons
	$('#stop').click(function(){
		sendCommandViaUDP("stop");
	});
	
	socket.on('udpMsg', function(result) {
		// Parse the first command to see what to do with the data
		var slicedResult = result.split(" ");

		if (slicedResult[0] === "screen") {
            // Convert the screen string to an array
            let stage = Number(slicedResult[1]);
            let pixels = petStages[stage];
            setPetScreen(pixels);
		}
		else {
			console.log(`MSG: ${result}`);
		}
	});

	// 
	https://stackoverflow.com/questions/7188145/call-a-javascript-function-every-5-seconds-continuously
	var intervalId = window.setInterval(function () {
		sendCommandViaUDP("get-pet-screen")
	}, 1000);
});

function sendCommandViaUDP(message) {
	var nodeReply = false;
	var clientReply = false;
	socket.emit('udpOut', message, (clientResponse) => {
		clientReply = clientResponse;
	});
	socket.emit('nodeUp', (nodeResponse) => {
		nodeReply = nodeResponse;
	});
	setTimeout(()=> {
		if (!nodeReply) {
			$('#error-box').show();
			$('#error-text').text('Node JS Server not responding...');
		}
		else if(!clientReply) {
			$('#error-box').show();
			$('#error-text').text('Client not responding...');
		}
		if (clientReply && nodeReply){
			$('#error-box').hide();
			$('#error-text').text('');
		}
	}, 1000);
};

// Pass in a 16x16 array to display on pet screen 
function setPetScreen(pixels) {
	let n = pixels.length;
	let m = pixels[0].length;
	let table = document.getElementById('petScreen');
    $("#petScreen tr").remove();
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
    menuForm.innerHTML ='';
    for (let i=0; i < n; i++) {
        menuForm.appendChild(menuBtns[i]);
    }
}

function initMenus() {
    // Main menu
    var interactButton = document.createElement('button');
    var feedButton = document.createElement('button');

    // TODO: Interact menu 

    // Feed menu
    var backButton = document.createElement('button');
    var waterButton = document.createElement('button');
    var foodButton = document.createElement('button');

    backButton.innerHTML = 'Back';
    waterButton.innerHTML = 'Water';
    foodButton.innerHTML = 'Food';

    interactButton.innerHTML = 'Interact';
    feedButton.innerHTML = 'Feed';

    interactButton.addEventListener('click', () => {
        console.log("Interact")
    });
    feedButton.addEventListener('click', () => {
        setMenuItems(feedMenu);
    });
    foodButton.addEventListener('click', () => {
        sendCommandViaUDP("feed food");
    });
    waterButton.addEventListener('click', () => {
        sendCommandViaUDP("feed water");
    });
    backButton.addEventListener('click', () => {
        setMenuItems(mainMenu);
    });

    mainMenu.push(interactButton);
    mainMenu.push(feedButton);

    feedMenu.push(waterButton);
    feedMenu.push(foodButton);
    feedMenu.push(backButton);

    setMenuItems(mainMenu);
}

initMenus();
