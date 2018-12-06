<?php
include_once('../app/api/session/session_api.php');
class SessionModel extends Phalcon\Mvc\Model
{

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Add Session /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
public function AddSession($user_id)
{
$SessionApi = new SessionApi();
$session_id = $SessionApi->AddSession();
$SessionApi->SetSessionUserId($session_id, $user_id);
$session_hash = SessionModel::GenerateSessionHash();
$SessionApi->SetSessionHash($session_id, $session_hash);
$SessionApi->SetSessionStatus($session_id, 'true');
$session_ip_address = $_SERVER['REMOTE_ADDR'];
$SessionApi->SetSessionIpAddress($session_id, $session_ip_address);
$session_http_user_agent = $_SERVER['HTTP_USER_AGENT'];
$SessionApi->SetSessionHttpUserAgent($session_id, $session_http_user_agent);
if($session_id){return $session_id;}else{return false;}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Add Session Extend //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
public function AddSessionExtend($user_id)
{
	$session_id = SessionModel::AddSession($user_id);
	if($session_id)
	{
		$check_cookie = SessionModel::SetSessionCookie($session_id);
		if($check_cookie)
		{
		return true;
		}
		else
		{
		return false;
		}
	}
	else
	{
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Generate Session Hash ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
public function GenerateSessionHash()
{
	$SessionApi = new SessionApi();

	for ($i = 0; $i < 10; $i++) 
	{
		$session_hash = bin2hex(openssl_random_pseudo_bytes(32));
		$id_check = $SessionApi->GetSessionIdWhere('session_hash', $session_hash);
		if($id_check)
		{
		//HASH ist vorhanden interiere weiter
		}
		else
		{
		//HASH ist noch frei breche schleife ab
		break 1;
		}
	}
	if($session_hash){return $session_hash;}else{return false;}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Set Session Cookie //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
public function SetSessionCookie($session_id)
{
	$SessionApi = new SessionApi();

	$name=$this->config->session_name;
	$value=$SessionApi->GetSessionHash($session_id);
	$expire=$this->config->session_time;
	$path=$this->config->session_path;
	$domain=$_SERVER['SERVER_NAME'];
	$secure=false;
	$httponly=true;
	$check = setcookie($name, $value, $expire, $path, $domain, $secure, $httponly);
	if($check){return true;}else{return false;}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Get Current User Id /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
public function GetCurrentUserId()
{
	$SessionApi = new SessionApi();
	$session_id = SessionModel::GetCurrentSessionId();
	if($session_id)
	{
		$user_id = $SessionApi->GetSessionUserId($session_id);
		if($user_id)
		{
			return $user_id;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Get Current Session Id //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
public function GetCurrentSessionId()
{
	$session_name=$this->config->session_name;

	if(isset($_COOKIE[$session_name]))
	{
		$cookie_value = $_COOKIE[$session_name];
		$SessionApi = new SessionApi();
		$session_id = $SessionApi->GetSessionIdWhereAndWhere('session_hash', $cookie_value, 'session_status', 'true');
		if($session_id)
		{
			return $session_id;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Destroy Current Session /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
public function DestroyCurrentSession()
{
		$session_id = SessionModel::GetCurrentSessionId();
		if($session_id)
		{
			$SessionApi = new SessionApi();
			$check = $SessionApi->SetSessionStatus($session_id, 'logout');
			if($check){return true;}else{return false;}
		}
		else
		{
			return false;
		}
}

}//end class
