<?php

///////////////////////////////////////////////////////////////////////////////
/// @file ConstantDocCommentsFilter.php
/// @title ConstantDocCommentsFilter class
/// @brief Filter & Parses the class for constant DocComments
///
/// @author justin
/// @date 2014. 8. 24. 오전 11:35:46
///////////////////////////////////////////////////////////////////////////////
 
class ConstantDocCommentsFilter
{
    // Constant names to DocComment strings
    private $docComments = [];

    // Constructor
    public function __construct($class)
    {
        $this->Parse(new \ReflectionClass($class));
    }

    // Parses the class for constant DocComments
    private function Parse(\ReflectionClass $class)
    {
        $content = file_get_contents($class->getFileName());
        $tokens = token_get_all($content);

        $doc = null;
        $isConst = false;
        foreach($tokens as $token)
        {
        	// filter non-array !!! 
        	if( false == is_array($token) ) {
        		continue;
        	}
        	
            list($tokenType, $tokenValue) = $token;
            
            switch ($tokenType)
            {
                // ignored tokens
                case T_WHITESPACE:
                case T_COMMENT:
                    break;

                case T_DOC_COMMENT:
                    $doc = $tokenValue;
                    break;

                case T_CONST:
                    $isConst = true;
                    break;

                case T_STRING:
                    if ($isConst)
                    {
                        $this->docComments[$tokenValue] = self::Clean($doc);
                    }
                    $doc = null;
                    $isConst = false;
                    break;

                // all other tokens reset the parser
                default:
                    $doc = null;
                    $isConst = false;
                    break;
            }
        }
    }

    // Returns an array of all constants to their DocComment.
    // If no comment is present the comment is null.
    public function GetDocComments()
    {
        return $this->docComments;
    }

    // Returns the DocComment of a class constant.
    // Null if the constant has no DocComment or the constant does not exist.
    public function GetDocComment($constantName)
    {
        if (!isset($this->docComments))
        {
            return null;
        }

        return $this->docComments[$constantName];
    }

    /** Cleans the doc comment. Returns null if the doc comment is null. */
    private static function Clean($doc)
    {
        if ($doc === null)
        {
            return null;
        }

        $result = null;
        $lines = preg_split('/\n/', $doc);
        for( $i = 0; $i < count($lines); $i++ )
        {
            $result .= $lines[$i];
            if( count($lines) > ($i + 1) ) {
            	$result .= "\n";
            }
        }
        
        return $result;
    }
}

?>