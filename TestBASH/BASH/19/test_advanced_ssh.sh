#!/bin/bash

################################################################################
# mongos2대, config3대, (mongod1대, 레플리카셋1대, 아비터1대)x2 세트 설치
#
# PS. 정상적으로 실행되지 않는 경우가 많으므로 설치 후
#     반드시 제대로 설치 되었는지 체크할것!
################################################################################


################################################################################
# 기본 정보 셋팅
################################################################################
USER=root
PASSWORD=kang14
DEFAULT_PATH="/service/test"

echo -e \\033[32m"############################################################"\\033[0m
echo -e \\033[32m"## UserID: $USER, PW: $PASSWORD"\\033[0m
echo -e \\033[32m"## Host: $DEFAULT_PATH"\\033[0m


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

# Distributed Server information setup
REMOTE_SERVER_SET=( "rs_1" "rs_2" )
REMOTE_SERVER_HOST_PORT=( 30100 30200 )
REMOTE_SERVER_HOST=( "192.168.1.105:${REMOTE_SERVER_HOST_PORT[0]}" "192.168.1.105:${REMOTE_SERVER_HOST_PORT[1]}" )


################################################################################
# MongoDB
################################################################################
g_hostAddr=""

function SetHostAddress()
{
	foundPos=`expr index "$1" :`
	let "foundPos-=1"
	g_hostAddr=`expr substr "$1" 1 $foundPos`
}

function ExecSSH()
{
	setsid ssh ${SSH_OPTIONS} ${USER}@$1 "$2"
}

function ExecSCP()
{
	setsid scp ${SSH_OPTIONS} "$1" "$2"
}

echo -e \\033[32m"## Remote SSH Processing..."\\033[0m

SetHostAddress ${REMOTE_SERVER_HOST[0]}
path=$DEFAULT_PATH/${REMOTE_SERVER_SET[0]}

echo -e \\033[32m"## Target HostAddr:$g_hostAddr"\\033[0m
ExecSSH $g_hostAddr "test -d $path || mkdir -p $path"

message="Hey~ girl ^^"

cat <<EOF > /tmp/message.txt
$message
EOF

# secure copy by remote !!!
ExecSCP /tmp/message.txt ${USER}@$g_hostAddr:/tmp/
# copy Local
ExecSSH $g_hostAddr "cp /tmp/message.txt $path"

# remove path !!!
ExecSSH $g_hostAddr "rm -fr /tmp/message.txt"
ExecSSH $g_hostAddr "rm -fr $DEFAULT_PATH"

exit 0
