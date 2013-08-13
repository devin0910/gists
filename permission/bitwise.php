<?php

class Perm
{
	const READ    = 1;
	const EDIT    = 2;
	const PUBLISH = 4;
	const DELETE  = 8;
}

$guest = Perm::READ;
$editor = $guest | Perm::EDIT;
$moderator = $editor | Perm::PUBLISH;
$publisher = $moderator & ~Perm::EDIT;
$admin = $moderator | Perm::DELETE;

$roles = array(
	'Guest' => $guest,
	'Editor' => $editor,
	'Moderator' => $moderator,
	'Publisher' => $publisher,
	'Administrator' => $admin,
);

$perms = array(
	'read' => Perm::READ,
	'edit' => Perm::EDIT,
	'publish' => Perm::PUBLISH,
	'delete' => Perm::DELETE,
);


function checkPerms($roles, $perms)
{
	foreach ($roles as $k => $v) {
		echo '<b>', $k, '</b><br/>';
		foreach ($perms as $pk => $pv) {
			if ($v & $pv)
				echo '- can ', $pk, '<br/>';
			else
				echo '- can not ', $pk, '<br/>';
		}
		echo '<br/>';
	}
}

checkPerms($roles, $perms);