#!/usr/bin/env sh
# generated from catkin/cmake/templates/env.sh.in

if [ $# -eq 0 ] ; then
  /bin/echo "Entering environment at '/home/rsd/workspace/RSD09/ROBOT_CONTROL/build/devel', type 'exit' to leave"
  . "/home/rsd/workspace/RSD09/ROBOT_CONTROL/build/devel/setup.sh"
  "$SHELL" -i
  /bin/echo "Exiting environment at '/home/rsd/workspace/RSD09/ROBOT_CONTROL/build/devel'"
else
  . "/home/rsd/workspace/RSD09/ROBOT_CONTROL/build/devel/setup.sh"
  exec "$@"
fi
