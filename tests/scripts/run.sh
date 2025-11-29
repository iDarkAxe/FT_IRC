#!/bin/bash

SERVER="./ircserv"
PORT=6667
PASS="password"
CLIENT_DIR="tests/irc_tester"

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

log() {
    echo -e "\n====$*===="
}

kill_server() {
    if [[ -n "$SERVER_PID" ]]; then
        kill "$SERVER_PID" 2>/dev/null || true
    fi
}
trap kill_server EXIT

# Port < 0
# Port 0 -> 1024
# port > 65535  

log "Starting server on port $PORT..."
$SERVER "$PORT" "$PASS" > .server.log 2>&1 &
SERVER_PID=$!

sleep 1

if kill -0 "$SERVER_PID" 2>/dev/null; then
echo -e "${GREEN}Server PID: $SERVER_PID${NC}"
else
    echo "Server failed to start"
    echo "--- Server log ---"
    cat .server.log
    exit 1
fi

if command -v kitty &>/dev/null; then
    kitty --title "IRC Server Log" watch -n 0.1 tail -45 .server.log &
    KITTY_PID=$!
fi


sleep 1

ulimit -n 65535
log "Starting Rust tester..."
(
    cd "$CLIENT_DIR"
    cargo run -- $1 
)

echo "Killing server PID: $SERVER_PID"
kill $SERVER_PID

ulimit -n 1024

log "======= Server log ======="
# verbose mode
errors_total=$(grep -c "ERROR" .server.log)
errors_unique=$(grep "ERROR" .server.log | sort | uniq | wc -l)
pings=$(grep -c "PING" .server.log)
pongs=$(grep -c "PONG" .server.log)
timeouts=$(grep -c "timed out" .server.log)
connections=$(grep -c "New client" .server.log)
registrations=$(grep -c "successfully registered" .server.log)

printf "%-25s : %5d (unique: %d)\n" "Errors" "$errors_total" "$errors_unique"
printf "%-25s : %5d\n" "Pings sent" "$pings"
printf "%-25s : %5d\n" "Pongs received" "$pongs"
printf "%-25s : %5d\n" "Timed out kicks" "$timeouts"
printf "%-25s : %5d\n" "Connections" "$connections"
printf "%-25s : %5d\n" "Registrations" "$registrations"
echo

if [[ -n "$KITTY_PID" ]]; then
    echo "Killing log watcher (kitty) PID: $KITTY_PID"
    kill "$KITTY_PID" 2>/dev/null || true
fi
