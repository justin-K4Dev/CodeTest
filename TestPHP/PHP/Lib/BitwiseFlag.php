<?php 

class BitwiseFlag
{
	protected $_flags;

	public function IsFlag( $flag )
	{
		return ( ($this->_flags & $flag) == $flag );
	}

	public function SetFlag( $flag, $value )
	{
		if( $value )
		{
			$this->_flags |= $flag;
		}
		else
		{
			$this->_flags &= ~$flag;
		}
	}
}

?>