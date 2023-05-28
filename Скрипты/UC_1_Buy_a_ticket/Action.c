Action()
{

	lr_start_transaction("1_script_buy_a_ticket");

	web_add_auto_header("Sec-Fetch-Site", 
		"none");

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	opensite();

	
	web_set_sockets_option("SSL_VERSION", "2&3");
	
	
	lr_think_time(5);

	login();

	
	

	
		
	gotoflight();
	lr_think_time(5);	
	
	lr_start_transaction("fing_flight");
	
/*Correlation comment - Do not change!  Original value='192;271;05/1/2023' Name ='outboundFlight' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=outboundFlight",
		"TagName=input",
		"Extract=value",
		"Name=outboundFlight",
		"Type=radio",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		LAST);
		
	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_reg_find("Text=Flight departing from ",
		LAST);
		
		web_reg_find("Text=from <B>{DepartureCity}</B> to <B>{ArrivalCity}</B> on <B>{departDate}</B>",
		LAST);
	 web_reg_find("Text=from <B>{ArrivalCity}</B> to <B>{DepartureCity}</B> on <B>{returnDate}</B>",
		LAST);
		web_reg_save_param("outboundFlight",
		"LB/IC=name=\"outboundFlight\" value=\"",
		"RB/IC=\"",
		"Ord=ALL",
		LAST);

	
	web_reg_save_param("returnFlight",
		"LB/IC=\"returnFlight\" value=\"",
		"RB/IC=\"",
		"Ord=ALL",
		LAST);
		
		


	



	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={DepartureCity}", ENDITEM, 
		"Name=departDate", "Value={departDate}", ENDITEM, 
		"Name=arrive", "Value={ArrivalCity}", ENDITEM, 
		"Name=returnDate", "Value={returnDate}", ENDITEM, 
		"Name=numPassengers", "Value={countPass}", ENDITEM,
		"Name=roundtrip", "Value={roundtrip}", ENDITEM,
		"Name=seatPref", "Value={seating_preference}", ENDITEM, 
		"Name=seatType", "Value={type_of_seat}", ENDITEM, 
		"Name=findFlights.x", "Value=55", ENDITEM, 
		"Name=findFlights.y", "Value=11", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);
		lr_save_string(lr_paramarr_random("outboundFlight"), "randomFlight");
		

	lr_end_transaction("fing_flight",LR_AUTO);

	
	
	
	lr_think_time(5);

	lr_start_transaction("select_ticket");
	
	web_reg_find("Text=Street Address",
		LAST);
	
	
	web_reg_find("Text/IC=\"outboundFlight\" value=\"{randomFlight}\"",
		LAST);
	
		
	

	web_submit_data("reservations.pl_2",
		"Action=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl",
		"Snapshot=t12.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=outboundFlight", "Value={randomFlight}", ENDITEM,
		"Name=numPassengers", "Value={countPass}", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=seatType", "Value={type_of_seat} ", ENDITEM,
		"Name=seatPref", "Value={seating_preference}", ENDITEM,
		"Name=reserveFlights.x", "Value=48", ENDITEM,
		"Name=reserveFlights.y", "Value=13", ENDITEM,
		LAST);

	lr_end_transaction("select_ticket",LR_AUTO);

	
	lr_think_time(5);
	
	lr_start_transaction("payment_details");

	web_revert_auto_header("Origin");

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_reg_find("Text=Reservation Made!",
		LAST);

	web_submit_data("reservations.pl_3",
		"Action=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl",
		"Snapshot=t13.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=firstName", "Value={FirstName}", ENDITEM,
		"Name=lastName", "Value={LastName}", ENDITEM,
		"Name=address1", "Value={adress}", ENDITEM,
		"Name=address2", "Value={adress2}", ENDITEM,
		"Name=pass1", "Value= {FirstName} {LastName}", ENDITEM,
		"Name=pass2", "Value={FirstName2} {LastName2} ", ENDITEM,
		"Name=pass3", "Value= {FirstName3}{LastName3}",ENDITEM,
		"Name=creditCard", "Value={creditcard}", ENDITEM,
		"Name=expDate", "Value={exp_date}" , ENDITEM,
		"Name=oldCCOption", "Value=", ENDITEM,
		"Name=numPassengers", "Value={countPass}", ENDITEM,
		"Name=seatType", "Value={type_of_seat}", ENDITEM,
		"Name=seatPref", "Value={seating_preference}", ENDITEM,
		"Name=outboundFlight", "Value={randomFlight} ", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=returnFlight", "Value=", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		"Name=buyFlights.x", "Value=62", ENDITEM,
		"Name=buyFlights.y", "Value=11", ENDITEM,
		"Name=.cgifields", "Value=saveCC", ENDITEM,
		LAST);

	lr_end_transaction("payment_details",LR_AUTO);

	
	lr_think_time(5);
	check_tiket();
	
	

	lr_end_transaction("1_script_buy_a_ticket", LR_AUTO);

	
	return 0;
}