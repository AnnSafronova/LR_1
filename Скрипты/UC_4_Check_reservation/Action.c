Action()
{
	lr_start_transaction("04_check_reserv");

	goToSite();
		

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
				"Name=login.x", "Value=72", ENDITEM,
				"Name=login.y", "Value=7", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				LAST);
			
		lr_end_transaction("login", LR_AUTO);

		lr_think_time(21);
		//
		
		lr_start_transaction("viewing_receipt");

			web_add_auto_header("Sec-Fetch-User",
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			web_reg_find("Fail=NotFound",
				"Text=User wants the intineraries",
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
	
		lr_end_transaction("viewing_receipt", LR_AUTO);
			
		lr_think_time(6);
			
		Logout();


	lr_end_transaction("04_check_reserv", LR_AUTO);

	return 0;
}