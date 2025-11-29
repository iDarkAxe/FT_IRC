#!/bin/bash

SERVER="./ircserv"
PORT=6667
PASS="password"
CLIENT_DIR="tests/irc_tester"

kill_server() {
    if [[ -n "$SERVER_PID" ]]; then
        kill "$SERVER_PID" 2>/dev/null || true
    fi
}
trap kill_server EXIT

# Port < 0
# Port 0 -> 1024
# port > 65535  

echo "Starting server on port $PORT..."
$SERVER "$PORT" "$PASS" > .server.log 2>&1 &
SERVER_PID=$!

sleep 1

if kill -0 "$SERVER_PID" 2>/dev/null; then
    echo "Server PID: $SERVER_PID"
else
    echo "Server failed to start"
    echo "--- Server log ---"
    cat .server.log
    exit 1
fi

sleep 1

ulimit -n 65535
echo "Starting Rust tester..."
(
    cd "$CLIENT_DIR"
    cargo run
)

echo "Kill " $SERVER_PID 
kill $SERVER_PID

ulimit -n 1024

echo "--- Server log ---"
# verbose mode
errors_total=$(grep -c "ERROR" .server.log)
errors_unique=$(grep "ERROR" .server.log | sort | uniq | wc -l)
pings=$(grep -c "PING" .server.log)
pongs=$(grep -c "PONG" .server.log)
timeouts=$(grep -c "timed out" .server.log)
connections=$(grep -c "New client" .server.log)
registrations=$(grep -c "successfully connected" .server.log)

printf "%-25s : %5d (unique: %d)\n" "Errors" "$errors_total" "$errors_unique"
printf "%-25s : %5d\n" "Pings sent" "$pings"
printf "%-25s : %5d\n" "Pongs received" "$pongs"
printf "%-25s : %5d\n" "Timed out kicks" "$timeouts"
printf "%-25s : %5d\n" "Connections" "$connections"
printf "%-25s : %5d\n" "Registrations" "$registrations"
