#!/bin/bash

################################################################################
# 기본 정보 셋팅
################################################################################
USER=root
PASSWORD=kang14
SERVER=192.168.1.105
MONGO_PATH="/service/mongodb"

echo -e \\033[32m "############################################################" \\033[0m
echo -e \\033[32m "UserID: $USER, PW: $PASSWORD" \\033[0m
echo -e \\033[32m "Host: $SERVER" \\033[0m

################################################################################
# 상세 셋팅
################################################################################
# Create a temp script to echo the SSH password, used by SSH_ASKPASS
SSH_ASKPASS_SCRIPT=/tmp/ssh-askpass-script
cat > ${SSH_ASKPASS_SCRIPT} <<EOL
#!/bin/bash
echo "${PASSWORD}"
EOL
chmod u+x ${SSH_ASKPASS_SCRIPT}
 
# Set up other items needed for OpenSSH to work. ###############################
# Set no display, necessary for ssh to play nice with setsid and SSH_ASKPASS.
export DISPLAY=:0
 
# Tell SSH to read in the output of the provided script as the password.
# We still have to use setsid to eliminate access to a terminal and thus avoid
# it ignoring this and asking for a password.
export SSH_ASKPASS=${SSH_ASKPASS_SCRIPT}
 
# LogLevel error is to suppress the hosts warning. The others are
# necessary if working with development servers with self-signed 
# certificates.
SSH_OPTIONS="-oLogLevel=error"
SSH_OPTIONS="${SSH_OPTIONS} -oStrictHostKeyChecking=no"
SSH_OPTIONS="${SSH_OPTIONS} -oUserKnownHostsFile=/dev/null"


################################################################################
# Stop
################################################################################
echo -e \\033[32m "## Do you want to stop all mongodb ? [yn]: " \\033[0m
read STOP_YN
if [ "$STOP_YN" = "y" ]; then
  CMD="service mongod stop"	
  setsid ssh ${SSH_OPTIONS} ${USER}@${SERVER} "${CMD}"
fi
sleep 5

################################################################################
# Start
################################################################################
echo -e \\033[32m "## Do you want to start all mongodb ? [yn]: " \\033[0m
CMD="service mongod start"
read START_YN
if [ "$START_YN" = "y" ]; then
  CMD="service mongod start"	
  setsid ssh ${SSH_OPTIONS} ${USER}@${SERVER} "${CMD}"
fi
sleep 5

