<?php

require_once 'Memcached.php';

class SmartLock
{
	private $_mainKey = null;
	private $_subKey = 'unknown';

	function __destruct() {

		$this->Unlock();
	}

	public function SmartLock() {
		
		$name = "SmartLock".func_num_args();
		$this->$name();
	}

	public function SmartLock1( $mainKey ) {

		$this->$_mainKey = $mainKey;

		$this->Lock();
	}

	public function SmartLock2( $mainKey, $objKey ) {

		$this->$_mainKey = $mainKey;
		$this->$_subKey = $objKey;

		$this->Lock();
	}

	public function Lock()
	{		
		$lock = MC::Get($this->$_mainKey, $this->$_subKey);
		if( $lock ) {
			for ( $i = 0; $i < 2; $i++ ) {
				$lock = MC::Inc($this->$_mainKey, $this->$_subKey, 1);
				if( $lock > 1 ) {
					sleep( 1 );
				}
				else {
					$result = true;
				}	
			}
		}
		else {
			MC::Set($this->$_mainKey, $this->$_subKey, 1, 2);
			$result = true;			
		}

		print("Called Lock ~~~~~ ~~~~~ ~~~~~ ~~~~~\n");

		return $result;
	}

	public function Unlock()
	{
		MC::Set($this->$_mainKey, $this->$_subKey, 0, 2);

		print("Called Unlock ~~~~~ ~~~~~ ~~~~~ ~~~~~\n");
	}
}

?>
