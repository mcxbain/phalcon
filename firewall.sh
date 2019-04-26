#!/bin/bash

#############################################################
#FIREWALL MAKE RESET
#############################################################
iptables -Z
iptables -F
iptables -X
iptables -t nat -F
iptables -t nat -X
iptables -t mangle -F
iptables -t mangle -X
iptables -P INPUT ACCEPT
iptables -P FORWARD ACCEPT
iptables -P OUTPUT ACCEPT
#############################################################

#############################################################
#FIREWALL ALLOW LOOPBACK
#############################################################
iptables -A INPUT -i lo -j ACCEPT
iptables -A OUTPUT -o lo -j ACCEPT
#############################################################

#############################################################
#FIREWALL ALLOW SSH
#############################################################
iptables -A INPUT -p tcp --dport 22 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
iptables -A OUTPUT -p tcp --sport 22 -m conntrack --ctstate ESTABLISHED -j ACCEPT
#############################################################

#############################################################
#FIREWALL ALLOW HTTP
#############################################################
iptables -A INPUT -p tcp --sport 80 -m state --state ESTABLISHED -j ACCEPT
iptables -A INPUT -p tcp --dport 80 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
iptables -A OUTPUT -p tcp --sport 80 -m conntrack --ctstate ESTABLISHED -j ACCEPT
iptables -A OUTPUT -p tcp --dport 80 -m state --state NEW,ESTABLISHED -j ACCEPT
#############################################################

#############################################################
#FIREWALL ALLOW HTTPS
#############################################################
iptables -A INPUT -p tcp --sport 443 -m state --state ESTABLISHED -j ACCEPT
iptables -A INPUT -p tcp --dport 443 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
iptables -A OUTPUT -p tcp --sport 443 -m conntrack --ctstate ESTABLISHED -j ACCEPT
iptables -A OUTPUT -p tcp --dport 443 -m state --state NEW,ESTABLISHED -j ACCEPT
#############################################################

#############################################################
#FIREWALL ALLOW PING
#############################################################
iptables -A INPUT -p icmp -j ACCEPT
iptables -A OUTPUT -p icmp -j ACCEPT
#############################################################

#############################################################
#FIREWALL ALLOW DNS
#############################################################
iptables -A INPUT -p udp --sport 53 -j ACCEPT
iptables -A OUTPUT -p udp --dport 53 -j ACCEPT
#############################################################

#############################################################
#FIREWALL ALLOW SMTP
#############################################################
iptables -A INPUT -p tcp --sport 587 -j ACCEPT
iptables -A INPUT -p tcp --dport 587 -j ACCEPT
iptables -A OUTPUT -p tcp --sport 587 -j ACCEPT
iptables -A OUTPUT -p tcp --dport 587 -j ACCEPT
#############################################################

#############################################################
#FIREWALL MAKE POLICY
#############################################################
iptables -P INPUT DROP
iptables -P FORWARD DROP
iptables -P OUTPUT DROP
#############################################################
