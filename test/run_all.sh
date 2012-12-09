#!/usr/bin/env bash
TESTDIR=$(dirname $0)
prog=$1

grepin() {
  grep -oP '(?<=^> ).*$'
}

grepout() {
  grep -oP '(?<=^< ).*$'
}

status=0
for io in $TESTDIR/*.io; do

  # print header/title
  tput bold
  printf "%-$[$(tput cols)/2-3]s   %s\n" $io \
    "cat $io | grepin | $prog"
  tput sgr0

  # copy input lines and write output lines to run file
  #cat $io | grep '^> ' | sed 's/^>/]/' > $io.run
  cat $io | grepin | $prog >& $io.run

  # compare run file with expected file, ignoring input
  output=$(sed -e 's/^< //' -e 's/^>/]/' $io | grep -v '^] ' | 
           sdiff --ignore-space-change \
             --width=$(tput cols) - $io.run)
  this_status=$?
  [ $status -eq 0 ] && status=$this_status

  if which colordiff &> /dev/null; then
    echo "$output" | colordiff --difftype diffy
  else
    echo "$output"
  fi
  [ -z $PASSTHROUGH ] && [ $status -ne 0 ] && exit $status
done

exit $status

