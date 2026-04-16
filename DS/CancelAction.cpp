#include "CancelAction.h"
void CancelAction::Act() 
{
	res->CancelOVC(OrderID);
}
