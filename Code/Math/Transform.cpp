#include <Math\Transform.h>


Transform Transform::operator*(const Transform& _ls) const
{
	Transform ws;
	ws.position = this->position + this->orientation * (this->scale * _ls.position);
	ws.orientation = this->orientation * _ls.orientation;
	ws.scale = this->scale * (this->orientation * _ls.scale);
	return(ws);
}

Transform Transform::operator/(const Transform& _ps) const
{
	Transform ls;
	Quaternion _psConj = conjugate(_ps.orientation);
	ls.position = (_psConj * (this->position - _ps.position)) / _ps.scale;
	ls.orientation = _psConj * this->orientation;
	ls.scale = _psConj * (this->scale / _ps.scale);
	return(ls);
}

