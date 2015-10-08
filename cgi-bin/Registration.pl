#!/usr/bin/perl -wT

use CGI qw(:standard);
#use strict;
#use warnings;

print <<END;
Content-Type: text/html; charset=iso-8859-1

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN">
END

$regfile = '../data/members.csv';

$name = param('name');
$uname = param('uname');
$pass = param('password');

open(my $data, '<', $regfile) or die "Could not open '$regfile' $!\n";
 
while (my $line = <$data>) {
	  chomp $line;
	   
	    my @fields = split " " , $line;
	    
	    if ( $fields[1] eq $uname ) {
	    	    err();
	    }
      }

open(REG,">>$regfile") or fail();
print REG "$name $uname $pass\n";
close(REG);
print "<p>Registered!</p>";
print "<p><a href=\"http://cgi.cs.mcgill.ca/~rtando1\">Login to your account</a></p>"; 

sub fail {
	 print "<title>Error</title>",
         	"<p>Error: cannot record your registration!</p>";
         exit; 
}

sub err {

	print "<title>ERROR</title>"; 
	print "<p>Username already exists</p>";
	print "<p><a href=\"http://cgi.cs.mcgill.ca/~rtando1/registration.html\">Please enter a new username</a></p>";
	exit;
}
