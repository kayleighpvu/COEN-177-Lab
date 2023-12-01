# Name: Kayleigh Vu
# Date: 09/21/2023
# Title: Lab1 – Unix/Linux Commands and Basic Shell Programming
# Description: This program computes the area and circumference of a circle when given the value of the circle's radius from the user.  Must check if the radius input is a positive number.
#!/bin/sh

echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."

if [ $user = "kpvu" ] 
then
	echo "Now you can proceed!"
else
	echo "Check who logged in!"
	exit 1
fi

response="Yes"
while [ $response != "No" ]
do
    echo "Enter radius of circle: "
	read radius
    if [ $radius -gt 0 ]    #checking if radius input is positive
        area=`echo "$radius * $radius * 3.1415" | bc`   #calculating area of circle 
	    circumference=`echo "$radius * 2 * 3.1415" | bc`   #calculating circumference of circle 
    else
        echo "Please input positive integer"
        exit 1
    fi
    
    echo "The area of the circle is $area"  #print area for user
    echo "The circumference of the circle is $circumference"    #print circumference for usr
	echo "Would you like to repeat for another circle [Yes/No]?"
	read response
done
