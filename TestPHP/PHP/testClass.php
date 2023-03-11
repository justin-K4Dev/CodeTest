<?php

// set error report
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

// set locale
setlocale(LC_CTYPE, 'ko_KR.UTF-8');

$now = date('Y-m-d H:i:s', time());
echo "Update Date : $now";
echo "<br>";


class Network
{
	private $_command;
		
    function __construct()
    {
        $this->Init();
    }
	
	function Init()
	{
		print("############## Call #################");
	
		$this->_command = 10;		
	}
			
	public function GetCOMMAND()
	{
		print( $this->_command );
		return $this->_command;
	}
}

function g_GetNetwork()
{
    global $g_Network;
    if ($g_Network == null) {
        $g_Network = new Network;
    }
	
//    ($g_Network instanceof Network);
    
	return $g_Network;
}


class Something { 

	public $_x; 

    function __construct() {

		print( "Called Something.__construct() !!!" ); 
		echo "<br>";
	}

	function __destruct() {

		print( "Called Something.__destruct() !!!" );
		echo "<br>";
	}

	public function Something( $x ) {

		$this->SetX( $x ); 
	}

	public function SetX( $x ) {

		$this->_x = $x;
	}

	public function GetX() {

		return $this->_x;
	}
} 


class Another extends Something {
	
	public $_y;

    function __construct() {

		print( "Called Another.__construct() !!!" );
		echo "<br>";
	}

	function __destruct() {

		print( "Called Another.__destruct() !!!" );
		echo "<br>";
	}

	public function Another( $x, $y ) {
		
		$this->Something( $x );

		$this->SetY( $y );
	}

	public function SetY( $y ) {

		$this->_y = $y;
	}

	public function GetY() {

		return $this->_y;
	}

}


//$obj1 = new Something( 1000 );
//var_dump( $obj1 );

//$obj2 = new Another( 10, 100 );
//var_dump( $obj2 );


class MyClass {
/*
    function __construct() {

		print( "Called MyClass.__construct() !!!" );
		echo "<br>";
	}
*/
	function __destruct() {

		print( "Called MyClass.__destruct() !!!" );
		echo "<br>";
	}
	
	public function MyClass() {
		
		$name = "MyClass".func_num_args();
		$this->$name();
	}

	public function MyClass1( $x ) {
	
		print( "Called MyClass.MyClass1() !!!" );
		echo "<br>";		
	}

	public function MyClass2( $x, $y ) {
	
		print( "Called MyClass.MyClass2() !!!" );
		echo "<br>";		
	}

}


function testFunction()
{
	$obj1 = new MyClass( 1000 );
	var_dump( $obj1 );
	
	$obj2 = new MyClass( 10, 100 );
	var_dump( $obj2 );
	
	$obj3 = new MyClass( 1000 );
	var_dump( $obj3 );
	
	$obj4 = new MyClass( 10, 100 );
	var_dump( $obj4 );	
}


testFunction();

echo "###############################################################################";
echo "<br>";

sleep(10);

?>
