/*****************************************************************************

 @(#) File: src/drivers/sua_sccp.c

 -----------------------------------------------------------------------------

 Copyright (c) 2008-2015  Monavacon Limited <http://www.monavacon.com/>
 Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software: you can redistribute it and/or modify it under
 the terms of the GNU Affero General Public License as published by the Free
 Software Foundation, version 3 of the license.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
 details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>, or
 write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
 02139, USA.

 -----------------------------------------------------------------------------

 U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on
 behalf of the U.S. Government ("Government"), the following provisions apply
 to you.  If the Software is supplied by the Department of Defense ("DoD"), it
 is classified as "Commercial Computer Software" under paragraph 252.227-7014
 of the DoD Supplement to the Federal Acquisition Regulations ("DFARS") (or any
 successor regulations) and the Government is acquiring only the license rights
 granted herein (the license rights customarily provided to non-Government
 users).  If the Software is supplied to any unit or agency of the Government
 other than DoD, it is classified as "Restricted Computer Software" and the
 Government's rights in the Software are defined in paragraph 52.227-19 of the
 Federal Acquisition Regulations ("FAR") (or any successor regulations) or, in
 the cases of NASA, in paragraph 18.52.227-86 of the NASA Supplement to the FAR
 (or any successor regulations).

 -----------------------------------------------------------------------------

 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See http://www.openss7.com/

 *****************************************************************************/

static char const ident[] = "src/drivers/sua_sccp.c (" PACKAGE_ENVR ") " PACKAGE_DATE;

/*
 *  =========================================================================
 *
 *  SCCP Primitive --> SUA Message Translator
 *
 *  =========================================================================
 */
/*
 *  N_CONN_REQ --> CORE
 *  -------------------------------------------------------------------------
 *  Note:  The caller must have already assigned the Protcol Class, SLS, SRN,
 *  Credit (if class 3), saved the SOURCE address and DEST address.  This
 *  function just packages up the message.
 */
static mblk_t *
s_conn_req(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_CORE;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		*((uint32_t *) mp->b_wptr)++ = htonl(sp->flags);
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = htonl(sp->rc.id);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_SRN;
		*((uint32_t *) mp->b_wptr)++ = htonl(sp->srn);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_DEST;
		*((uint32_t *) mp->b_wptr)++ = FIXME;
		*((uint32_t *) mp->b_wptr)++ = FIXME;
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_SRCE;
		*((uint32_t *) mp->b_wptr)++ = FIXME;
		*((uint32_t *) mp->b_wptr)++ = FIXME;
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_CREDIT;
		*((uint32_t *) mp->b_wptr)++ = htonl(sp->credit);
		if (prim->b_cont) {
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_DATA;
			mp->b_cont = prim->b_cont;
		}
		freeb(prim);
	}
	return (mp);
}

/*
 *  N_CONN_RES --> COAK
 *  -------------------------------------------------------------------------
 *  SPECIFICATION NOTES:-  The COAK message does not have Network Appearance
 *	as an optional parameter.  This means that the effective range of the
 *	source reference number is reduced by the range of Network Appearances
 *	(because the network appearance is implicit in the source reference
 *	number).
 */
static mblk_t *
s_conn_res(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_COAK;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = htonl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_DRN;
		*((uint32_t *) mp->b_wptr)++ = htonl(sp->drn);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_SRN;
		*((uint32_t *) mp->b_wptr)++ = htonl(sp->srn);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_CREDIT;
		*((uint32_t *) mp->b_wptr)++ = htonl(sp->credit);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_DEST;
		*((uint32_t *) mp->b_wptr)++ = FIXME;
		*((uint32_t *) mp->b_wptr)++ = FIXME;
		if (prim->b_cont) {
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_DATA;
			mp->b_cont = prim->b_cont;
		}
		freeb(prim);
	}
	return (mp);
}

/*
 *  N_DISCON_REQ --> COREF, RELRE
 *  -------------------------------------------------------------------------
 *  There are three cases here:
 *	N_DISCON_REQ in NS_WRES_CIND	--> COREF
 *	N_DISCON_REQ in NS_DATA_XFER	--> RELRE
 *
 */
static mblk_t *
s_discon_req(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);

	switch (sp->state) {
	case NS_WRES_CIND:
	{
		static const size_t mlen = FIXME;

		if ((mp = allocb(mlen, BPRI_HI))) {
			mp->b_datap->db_type = M_DATA;
			*((uint32_t *) mp->b_wptr)++ = SUA_CONS_COREF;
			*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
			/* Note: need to set message priority in Flags */
			*((uint32_t *) mp->b_wptr)++ = htonl(sp->flags);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
			*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_DRN;
			*((uint32_t *) mp->b_wptr)++ = hotnl(sp->drn);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_CAUSE;
			*((uint32_t *) mp->b_wptr)++ = hotnl(cause);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_DEST;
			*((uint32_t *) mp->b_wptr)++ = FIXME;
			*((uint32_t *) mp->b_wptr)++ = FIXME;
			if (prim->b_cont) {
				*((uint32_t *) mp->b_wptr)++ = SUA_PARM_DATA;
				mp->b_cont = prim->b_cont;
			}
			freeb(prim);
		}
		return (mp);
	}
	default:
	case NS_DATA_XFER:
	{
		static const size_t mlen = FIXME;

		if ((mp = allocb(mlen, BPRI_HI))) {
			mp->b_datap->db_type = M_DATA;
			*((uint32_t *) mp->b_wptr)++ = SUA_CONS_RELRE;
			*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
			/* Note: need to set message priority in Flags */
			*((uint32_t *) mp->b_wptr)++ = htonl(sp->flags);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
			*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_DRN;
			*((uint32_t *) mp->b_wptr)++ = hotnl(sp->drn);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_SRN;
			*((uint32_t *) mp->b_wptr)++ = hotnl(sp->srn);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_CAUSE;
			*((uint32_t *) mp->b_wptr)++ = hotnl(sp->cause);
			if (prim->b_cont) {
				*((uint32_t *) mp->b_wptr)++ = SUA_PARM_DATA;
				mp->b_cont = prim->b_cont;
			}
			freeb(prim);
		}
		return (mp);
	}
	}
}

/*
 *  N_DATA_REQ --> CODT
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_data_req(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_CODT;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_SEQ_NUM;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->seq);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_DEST;
		*((uint32_t *) mp->b_wptr)++ = FIXME;
		*((uint32_t *) mp->b_wptr)++ = FIXME;

		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_EXDATA_REQ --> CODT
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_exdata_req(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_CODT;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_UNITDATA_REQ --> CLDT
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_unitdata_req(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_CLDT;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_DATACK_REQ --> CODA
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_datack_req(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_CODA;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_RESET_REQ --> RESRE
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_reset_req(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_RESRE;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_RESET_RES --> RESCO
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_reset_res(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_RESCO;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_CONN_IND --> CORE
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_conn_ind(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_CORE;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_CONN_CON --> COAK
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_conn_con(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_COAK;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_DISCON_IND --> COAK, RELRE, or RELCO
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_discon_ind(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);

	switch (sp->state) {
	case NS_WCON_CREQ:
	{
		static const size_t mlen = FIXME;

		if ((mp = allocb(mlen, BPRI_HI))) {
			mp->b_datap->db_type = M_DATA;
			*((uint32_t *) mp->b_wptr)++ = SUA_CONS_COAK;
			*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
			/* Note: need to set message priority in Flags */
			*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
			*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
			/* 
			 *  FIXME: More...
			 */
		}
		return (mp);
	}
	case NS_WACK_DREQ:
	{
		static const size_t mlen = FIXME;

		if ((mp = allocb(mlen, BPRI_HI))) {
			mp->b_datap->db_type = M_DATA;
			*((uint32_t *) mp->b_wptr)++ = SUA_CONS_RELCO;
			*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
			/* Note: need to set message priority in Flags */
			*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
			*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
			/* 
			 *  FIXME: More...
			 */
		}
		return (mp);
	}
	default:
	case NS_WIND_DREQ:
	{
		static const size_t mlen = FIXME;

		if ((mp = allocb(mlen, BPRI_HI))) {
			mp->b_datap->db_type = M_DATA;
			*((uint32_t *) mp->b_wptr)++ = SUA_CONS_RELRE;
			*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
			/* Note: need to set message priority in Flags */
			*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
			*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
			*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
			/* 
			 *  FIXME: More...
			 */
		}
		return (mp);
	}
	}
}

/*
 *  N_DATA_IND --> CODT
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_data_ind(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_CODT;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_EXDATA_IND --> CODT
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_exdata_ind(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_CODT;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_UNITDATA_IND --> CLDT
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_unitdata_ind(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CNLS_CLDT;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_UDERROR_IND --> CLDR
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_uderror_ind(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CNLS_CLDR;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_DATACK_IND --> CODA
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_datack_ind(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_CODA;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_RESET_IND --> RESRE
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_reset_ind(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_RESRE;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  N_RESET_CON --> RESCO
 *  -------------------------------------------------------------------------
 */
static mblk_t *
s_reset_con(queue_t *q, mblk_t *prim)
{
	mblk_t *mp;
	sccp_t *sp = Q_SCCP(q);
	static const size_t mlen = FIXME;

	if ((mp = allocb(mlen, BPRI_HI))) {
		mp->b_datap->db_type = M_DATA;
		*((uint32_t *) mp->b_wptr)++ = SUA_CONS_RESCO;
		*((uint32_t *) mp->b_wptr)++ = __constant_htonl(mlen);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_FLAGS;
		/* Note: need to set message priority in Flags */
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->flags);
		*((uint32_t *) mp->b_wptr)++ = SUA_PARM_RC;
		*((uint32_t *) mp->b_wptr)++ = hotnl(sp->rc.id);
		/* 
		 *  FIXME: More...
		 */
	}
	return (mp);
}

/*
 *  -------------------------------------------------------------------------
 *
 *  SCCP Primitive --> SUA Message Translation Table
 *
 *  -------------------------------------------------------------------------
 */

static mblk_t *(*s_xlat[]) (queue_t *, mblk_t *) = {
#define S_XLAT_FIRST	    N_CONN_REQ
	s_conn_req,		/* N_CONN_REQ 0 */
	    s_conn_res,		/* N_CONN_RES 1 */
	    s_discon_req,	/* N_DISCON_REQ 2 */
	    s_data_req,		/* N_DATA_REQ 3 */
	    s_exdata_req,	/* N_EXDATA_REQ 4 */
	    NULL,		/* N_INFO_REQ 5 */
	    NULL,		/* N_BIND_REQ 6 */
	    NULL,		/* N_UNBIND_REQ 7 */
	    s_unitdata_req,	/* N_UNITDATA_REQ 8 */
	    NULL,		/* N_OPTMGMT_REQ 9 */
	    NULL,		/* (not used) 20 */
	    s_conn_ind,		/* N_CONN_IND 21 */
	    s_conn_con,		/* N_CONN_CON 22 */
	    s_discon_ind,	/* N_DISCON_IND 23 */
	    s_data_ind,		/* N_DATA_IND 24 */
	    s_exdata_ind,	/* N_EXDATA_IND 25 */
	    NULL,		/* N_INFO_ACK 26 */
	    NULL,		/* N_BIND_ACK 27 */
	    NULL,		/* N_ERROR_ACK 28 */
	    NULL,		/* N_OK_ACK 29 */
	    s_unitdata_ind,	/* N_UNITDATA_IND 30 */
	    s_uderror_ind,	/* N_UDERROR_IND 31 */
	    NULL,		/* (not used) 32 */
	    s_datack_req,	/* N_DATACK_REQ 33 */
	    s_datack_ind,	/* N_DATACK_IND 34 */
	    s_reset_req,	/* N_RESET_REQ 35 */
	    s_reset_ind,	/* N_RESET_IND 36 */
	    s_reset_res,	/* N_RESET_RES 37 */
	    s_reset_con		/* N_RESET_CON 38 */
#define S_XLAT_LAST	    N_RESET_CON
};

/*
 *  =========================================================================
 *
 *  SUA Message --> SCCP Primitive Translator
 *
 *  =========================================================================
 */
