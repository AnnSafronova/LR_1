Action()
{
	
	int flight_id_num = 0;
	
	lr_start_transaction("02_delite");
	
		lr_start_transaction("goToSite");
		
			web_set_sockets_option("SSL_VERSION", "AUTO");
		
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
		
	
			web_reg_save_param_attrib(
				"ParamName=userSession",
				"TagName=input",
				"Extract=value",
				"Name=userSession",
				"Type=hidden",
				SEARCH_FILTERS,
				"RequestUrl=*/nav.pl*",
				LAST);
		
			web_reg_find("Fail=NotFound",
				"Text=Web Tours",
				LAST);
		
			web_url("WebTours", 
				"URL=http://localhost:1080/WebTours/", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=", 
				"Snapshot=t1.inf", 
				"Mode=HTML", 
				LAST);
		
		lr_end_transaction("goToSite", LR_AUTO);

		lr_think_time(6);
		
		lr_start_transaction("login");

			web_revert_auto_header("Sec-Fetch-User");
		
			web_add_auto_header("Sec-Fetch-Dest", 
				"frame");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_header("Origin", 
				"http://localhost:1080");
		
			web_add_auto_header("Sec-Fetch-Site", 
				"same-origin");
		
			web_reg_find("Fail=NotFound",
				"Text=User password was correct",
				LAST);
			
			web_submit_data("login.pl",
				"Action=http://localhost:1080/cgi-bin/login.pl",
				"Method=POST",
				"TargetFrame=body",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
				"Snapshot=t2.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=userSession", "Value={userSession}", ENDITEM,
				"Name=username", "Value={login}", ENDITEM,
				"Name=password", "Value={password}", ENDITEM,
				"Name=login.x", "Value=41", ENDITEM,
				"Name=login.y", "Value=14", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				LAST);
		
		lr_end_transaction("login", LR_AUTO);

		lr_think_time(16);
		
		lr_start_transaction("viewing_receipt");

			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			web_reg_find("Fail=NotFound",
				"Text=User wants the intineraries",
				LAST);	
		
			web_reg_save_param("flight_id",
				"LB=name=\"flightID\" value=\"",
				"RB=\"",
				"Ord=ALL",
				LAST);
		
			web_url("Itinerary Button",
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);
			
		flight_id_num = atoi(lr_eval_string("{flight_id_count}"));
		
		lr_end_transaction("viewing_receipt", LR_AUTO);

		lr_think_time(6);
			
		lr_start_transaction("cancel_booking");

			web_add_header("Origin", 
				"http://localhost:1080");
			
			web_reg_find("Fail=NotFound",
				"Text=Flight Transaction Summary",
				LAST);	
				
			web_reg_save_param("flights_numbers",
				"LB=<b>A total of ",
				"RB= scheduled flights.</font></b>",
				LAST);

			if (atoi(lr_eval_string("{delete_num}")) == 1){
				
				web_submit_form("web_submit_form",
					ITEMDATA,
					"Name=1", "Value=on", ENDITEM,
					"Name=removeFlights.x", "Value=33", ENDITEM,
					"Name=removeFlights.y", "Value=4", ENDITEM,
					EXTRARES,
					"URL=http://localhost:1080/cgi-bin/itinerary.pl",
					"Referer=http://localhost:1080/cgi-bin/itinerary.pl", ENDITEM,
					LAST);
			
			} else if (atoi(lr_eval_string("{delete_num}")) == 2){
				
				web_submit_form("web_submit_form",
					ITEMDATA,
					"Name=1", "Value=on", ENDITEM,
					"Name=2", "Value=on", ENDITEM,
					"Name=removeFlights.x", "Value=33", ENDITEM,
					"Name=removeFlights.y", "Value=4", ENDITEM,
					EXTRARES,
					"URL=http://localhost:1080/cgi-bin/itinerary.pl",
					"Referer=http://localhost:1080/cgi-bin/itinerary.pl", ENDITEM,
					LAST);
			
			} else if (atoi(lr_eval_string("{delete_num}")) == 3){
				
				web_submit_form("web_submit_form",
					ITEMDATA,
					"Name=1", "Value=on", ENDITEM,
					"Name=2", "Value=on", ENDITEM,
					"Name=3", "Value=on", ENDITEM,
					"Name=removeFlights.x", "Value=33", ENDITEM,
					"Name=removeFlights.y", "Value=4", ENDITEM,
					EXTRARES,
					"URL=http://localhost:1080/cgi-bin/itinerary.pl",
					"Referer=http://localhost:1080/cgi-bin/itinerary.pl", ENDITEM,
					LAST);
			
			}
		     
			if(atoi(lr_eval_string("{flights_numbers}")) >= flight_id_num)
				{
			    	lr_error_message("Itinerary not deleted");
				} 
			else if (atoi(lr_eval_string("{flights_numbers}")) < flight_id_num) 
				{
			        lr_output_message("Itinerary deleted succuess");
			    }

		lr_end_transaction("cancel_booking", LR_AUTO);
		
		lr_think_time(6);		
		
		lr_start_transaction("logout");

			web_revert_auto_header("Sec-Fetch-User");
		
			web_add_header("Sec-Fetch-User", 
				"?1");
		
			web_reg_find("Fail=NotFound",
				"Text=A Session ID has been created and loaded into a cookie called",
				LAST);
			
			web_url("SignOff Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
				"Snapshot=t5.inf", 
				"Mode=HTML", 
				LAST);
			
		lr_end_transaction("logout", LR_AUTO);

		
	lr_end_transaction("02_delite", LR_AUTO);

	return 0;
}