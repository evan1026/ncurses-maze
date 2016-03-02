session=maze
window=${session}:0
pane=${window}.0

touch times.txt

for size in 10 20 30 40 50 75 100 125 150 175 200; do
  for i in `seq 1 10`; do
    tmux send-keys -t "$pane" "mazegame $size $size" Enter
    tmux send-keys -t "$pane" Space s

    while [ -n "$(pgrep -P `tmux list-panes -t 0 -F '#{pane_pid}'`)" ]; do
      sleep 2
    done

    tmux copy-mode -t "$pane"
    tmux send-keys -t "$pane" Up Up Up C-Space C-a M-w
    tmux send-keys -t "$pane" "echo \"" "$size" "x" "$size" " : \"" "\$(echo "
    tmux paste -t "$pane"
    tmux send-keys -t "$pane" " | awk '{print \$3}') >> times.txt" Enter

    echo Done $size by $size trial $i
  done
done
