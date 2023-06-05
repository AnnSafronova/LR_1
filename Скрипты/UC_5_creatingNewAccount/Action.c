Action()
{


lr_start_transaction("06_CreatingNewAccount");
opensite();
lr_think_time(5);
	lr_start_transaction("Open_sign_up_now");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_reg_find("Text/IC=? Please complete the form below.<",
		LAST);

	web_url("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Open_sign_up_now",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("Filling_out_the_form");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_save_string(lr_eval_string("{n1}{n2}{n3}{n4}{n5}"), "randomName");
	
	web_reg_find("Text/IC=Thank you, <b>{randomName}</b>,",
		LAST);
 	web_submit_data("login.pl_2", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		
		"Name=username", "Value={randomName}", ENDITEM,
		"Name=password", "Value={randomName}", ENDITEM, 
		"Name=passwordConfirm", "Value={randomName}", ENDITEM, 
		"Name=firstName", "Value={flirstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={address1}", ENDITEM, 
		"Name=address2", "Value={address2}", ENDITEM, 
		"Name=register.x", "Value=54", ENDITEM, 
		"Name=register.y", "Value=9", ENDITEM, 
		LAST);

	lr_end_transaction("Filling_out_the_form",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("Continue");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	
	web_reg_find("Fail=NotFound",
				"Text=User has returned to the home page",
				LAST);

	web_url("button_next.gif", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Continue",LR_AUTO);
	lr_think_time(5);
	logout();
	

	
	lr_end_transaction("06_CreatingNewAccount",LR_AUTO);

	return 0;
}