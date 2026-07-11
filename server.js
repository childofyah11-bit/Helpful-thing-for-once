const http = require('http');
const WebSocket = require('ws');

// Simple web routing setup so cloud services know the server is active
const server = http.createServer((req, res) => {
    res.writeHead(200, { 'Content-Type': 'text/plain' });
    res.end('Multiplayer Game Server Engine is Running.');
});

const wss = new WebSocket.Server({ server });

// Server memory dictionary to track player positions in real time
let activePlayers = {};

wss.on('connection', (ws) => {
    // Assign a unique player identification string
    const playerId = 'player_' + Math.random().toString(36).substring(2, 9);
    
    // Spawn the player at a random spot inside the canvas arena parameters
    activePlayers[playerId] = {
        id: playerId,
        x: Math.floor(Math.random() * 700) + 50,
        y: Math.floor(Math.random() * 400) + 50,
        color: `hsl(${Math.random() * 360}, 80%, 60%)`
    };

    // Send the current game room state exclusively to the new connector
    ws.send(JSON.stringify({
        type: 'init',
        id: playerId,
        players: activePlayers
    }));

    // Alert all existing connections that a new challenger joined
    broadcast(JSON.stringify({
        type: 'newPlayer',
        player: activePlayers[playerId]
    }));

    // Listen for movement vectors arriving over the pipeline network
    ws.on('message', (message) => {
        try {
            const data = JSON.parse(message);
            if (data.type === 'move' && activePlayers[playerId]) {
                activePlayers[playerId].x = data.x;
                activePlayers[playerId].y = data.y;

                // Propagate coordinates live to keep maps uniform
                broadcast(JSON.stringify({
                    type: 'update',
                    id: playerId,
                    x: data.x,
                    y: data.y
                }));
            }
        } catch (e) {
            console.error("Payload decode error:", e);
        }
    });

    // Automatically remove historical tracking keys if a player disconnects
    ws.on('close', () => {
        delete activePlayers[playerId];
        broadcast(JSON.stringify({
            type: 'playerLeft',
            id: playerId
        }));
    });
});

// Broadcast transmission wrapper utility
function broadcast(payload) {
    wss.clients.forEach((client) => {
        if (client.readyState === WebSocket.OPEN) {
            client.send(payload);
        }
    });
}

// Bind server engine listener to automated production port environments
const PORT = process.env.PORT || 3000;
server.listen(PORT, () => {
    console.log(`Multiplayer sync gateway active on port: ${PORT}`);
});
