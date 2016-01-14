files=$(find $(dirname $0) -type f | xargs grep TODO)

set -f              # turn off globbing
IFS='
'                   # split at newlines only'
for file in $files; do
  if [[ $file != *$0* ]]; then
    echo $file
  fi
done

unset IFS
set +f
