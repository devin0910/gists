<?php

require_once __DIR__ . '/vendor/autoload.php';

require_once 'annotations.php';

use Doctrine\Common\Annotations\AnnotationReader;
 
$annotationReader = new AnnotationReader();

$path = __DIR__ .'/controller';

$directory = new RecursiveDirectoryIterator($path,RecursiveDirectoryIterator::SKIP_DOTS);
$iterator = new RecursiveIteratorIterator($directory,RecursiveIteratorIterator::LEAVES_ONLY);

foreach ($iterator as $fileinfo) {
    $files[] = $fileinfo->getBasename('.php');
}

var_dump($files);

foreach ($files as $class)
{
	require_once $path . "/$class.php";
	$reflectClass = new ReflectionClass($class);
	foreach ($reflectClass->getMethods(ReflectionMethod::IS_PUBLIC) as $method) {
		$methodName = $method->getName();
		// Method Annotations
$reflectionMethod = new ReflectionMethod($class, $methodName);
$methodAnnotations = $annotationReader->getMethodAnnotations($reflectionMethod);
 
 
echo "=========   Method ANNOTATIONS =========" . PHP_EOL;
var_dump($methodAnnotations);
	}
}