/*
 @(#) src/java/javax/jain/ss7/inap/operation/TerminationAttempt.java <p>
 
 Copyright &copy; 2008-2015  Monavacon Limited <a href="http://www.monavacon.com/">&lt;http://www.monavacon.com/&gt;</a>. <br>
 Copyright &copy; 2001-2008  OpenSS7 Corporation <a href="http://www.openss7.com/">&lt;http://www.openss7.com/&gt;</a>. <br>
 Copyright &copy; 1997-2001  Brian F. G. Bidulock <a href="mailto:bidulock@openss7.org">&lt;bidulock@openss7.org&gt;</a>. <p>
 
 All Rights Reserved. <p>
 
 This program is free software: you can redistribute it and/or modify it under
 the terms of the GNU Affero General Public License as published by the Free
 Software Foundation, version 3 of the license. <p>
 
 This program is distributed in the hope that it will be useful, but <b>WITHOUT
 ANY WARRANTY</b>; without even the implied warranty of <b>MERCHANTABILITY</b>
 or <b>FITNESS FOR A PARTICULAR PURPOSE</b>.  See the GNU Affero General Public
 License for more details. <p>
 
 You should have received a copy of the GNU Affero General Public License along
 with this program.  If not, see
 <a href="http://www.gnu.org/licenses/">&lt;http://www.gnu.org/licenses/&gt</a>,
 or write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
 02139, USA. <p>
 
 <em>U.S. GOVERNMENT RESTRICTED RIGHTS</em>.  If you are licensing this
 Software on behalf of the U.S. Government ("Government"), the following
 provisions apply to you.  If the Software is supplied by the Department of
 Defense ("DoD"), it is classified as "Commercial Computer Software" under
 paragraph 252.227-7014 of the DoD Supplement to the Federal Acquisition
 Regulations ("DFARS") (or any successor regulations) and the Government is
 acquiring only the license rights granted herein (the license rights
 customarily provided to non-Government users).  If the Software is supplied to
 any unit or agency of the Government other than DoD, it is classified as
 "Restricted Computer Software" and the Government's rights in the Software are
 defined in paragraph 52.227-19 of the Federal Acquisition Regulations ("FAR")
 (or any successor regulations) or, in the cases of NASA, in paragraph
 18.52.227-86 of the NASA Supplement to the FAR (or any successor regulations). <p>
 
 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See
 <a href="http://www.openss7.com/">http://www.openss7.com/</a>
 */

package javax.jain.ss7.inap.operation;

import javax.jain.ss7.inap.constants.*;
import javax.jain.ss7.inap.datatype.*;
import javax.jain.ss7.inap.*;
import javax.jain.ss7.*;
import javax.jain.*;

/** This class represents the TerminationAttempt Operation.
  * @version 1.2.2
  * @author Monavacon Limited
  */
public class TerminationAttempt extends Operation  implements java.io.Serializable {
    /** Constructor For TerminationAttempt.  */
    public TerminationAttempt(DPSpecificCommonParameters dPSpecificCommonParameters) {
        operationCode = OperationCode.TERMINATION_ATTEMPT;
        setDPSpecificCommonParameters(dPSpecificCommonParameters);
    }
    /** Gets Operation Code.  */
    public OperationCode getOperationCode() {
        return operationCode;
    }
    /** Gets Dp Specific Common Parameters.  */
    public DPSpecificCommonParameters getDPSpecificCommonParameters() {
        return dPSpecificCommonParameters;
    }
    /** Sets Dp Specific Common Parameters.  */
    public void setDPSpecificCommonParameters(DPSpecificCommonParameters dPSpecificCommonParameters) {
        this.dPSpecificCommonParameters = dPSpecificCommonParameters;
    }
    /** Gets Called Party BusinessGroupID.  */
    public java.lang.String getCalledPartyBusinessGroupID() throws ParameterNotSetException {
        if (isCalledPartyBusinessGroupID)
            return calledPartyBusinessGroupID;
        throw new ParameterNotSetException("Called Party Business Group Id: not set.");
    }
    /** Sets Called Party Business Group ID.  */
    public void setCalledPartyBusinessGroupID(java.lang.String calledPartyBusinessGroupID) {
        this.calledPartyBusinessGroupID = calledPartyBusinessGroupID;
        this.isCalledPartyBusinessGroupID = true;
    }
    /** Indicates if the Called Party BusinessGroupID optional parameter is present.
      * @return True when present, false otherwise.  */
    public boolean isCalledPartyBusinessGroupIDPresent() {
        return isCalledPartyBusinessGroupID;
    }
    /** Gets Called Party Subaddress.  */
    public CalledPartySubaddress getCalledPartySubaddress() throws ParameterNotSetException {
        if (isCalledPartySubaddress)
            return calledPartySubaddress;
        throw new ParameterNotSetException("Called Party Subaddress: not set.");
    }
    /** Sets Calling Party Subaddress.  */
    public void setCalledPartySubaddress(CalledPartySubaddress calledPartySubaddress) {
        this.calledPartySubaddress = calledPartySubaddress;
        this.isCalledPartySubaddress = true;
    }
    /** Indicates if the Calling Party Subaddress optional parameter is present.
      * @return True when present, false otherwise.  */
    public boolean isCalledPartySubaddressPresent() {
        return isCalledPartySubaddress;
    }
    /** Gets Calling Party BusinessGroupID.  */
    public java.lang.String getCallingPartyBusinessGroupID() throws ParameterNotSetException {
        if (isCallingPartyBusinessGroupID)
            return callingPartyBusinessGroupID;
        throw new ParameterNotSetException("Calling Party Business Group Id: not set.");
    }
    /** Sets Calling Party Business Group ID.  */
    public void setCallingPartyBusinessGroupID(java.lang.String  callingPartyBusinessGroupID) {
        this.callingPartyBusinessGroupID = callingPartyBusinessGroupID;
        this.isCallingPartyBusinessGroupID = true;
    }
    /** Indicates if the Calling Party BusinessGroupID optional parameter is present.
      * @return True when present, false otherwise.  */
    public boolean isCallingPartyBusinessGroupIDPresent() {
        return isCallingPartyBusinessGroupID;
    }
    /** Gets Calling Party Subaddress.  */
    public CallingPartySubaddress getCallingPartySubaddress() throws ParameterNotSetException {
        if (isCallingPartySubaddress)
            return callingPartySubaddress;
        throw new ParameterNotSetException("Calling Party Subaddress: not set.");
    }
    /** Sets Calling Party Subaddress.  */
    public void setCallingPartySubaddress(CallingPartySubaddress  callingPartySubaddress) {
        this.callingPartySubaddress = callingPartySubaddress;
        this.isCallingPartySubaddress = true;
    }
    /** Indicates if the Calling Party Subaddress optional parameter is present.
      * @return True when present, false otherwise.  */
    public boolean isCallingPartySubaddressPresent() {
        return isCallingPartySubaddress;
    }
    /** Gets Original Called Party ID.  */
    public OriginalCalledPartyID getOriginalCalledPartyID() throws ParameterNotSetException {
        if (isOriginalCalledPartyID)
            return originalCalledPartyID;
        throw new ParameterNotSetException("Original Called Party Id: not set.");
    }
    /** Sets Original Called Party ID.  */
    public void setOriginalCalledPartyID(OriginalCalledPartyID originalCalledPartyID) {
        this.originalCalledPartyID = originalCalledPartyID;
        this.isOriginalCalledPartyID = true;
    }
    /** Indicates if the Original Called Party ID optional parameter is present.
      * @return True when present, false otherwise.  */
    public boolean isOriginalCalledPartyIDPresent() {
        return isOriginalCalledPartyID;
    }
    /** Gets Redirecting Party ID.  */
    public RedirectingPartyID getRedirectingPartyID() throws ParameterNotSetException {
        if (isRedirectingPartyID)
            return redirectingPartyID;
        throw new ParameterNotSetException("Redirecting Party Id: not set.");
    }
    /** Sets Redirecting Party ID.  */
    public void setRedirectingPartyID(RedirectingPartyID redirectingPartyID) {
       this.redirectingPartyID = redirectingPartyID;
       this.isRedirectingPartyID = true;
    }
    /** Indicates if the Redirecting Party ID optional parameter is present.
      * @return True when present, false otherwise.  */
    public boolean isRedirectingPartyIDPresent() {
        return isRedirectingPartyID;
    }
    /** Gets Redirection Information.  */
    public RedirectionInformation getRedirectionInformation() throws ParameterNotSetException {
        if (isRedirectionInformation)
            return redirectionInformation;
        throw new ParameterNotSetException("Redirection Information: not set.");
    }
    /** Sets Redirection Information.  */
    public void setRedirectionInformation(RedirectionInformation redirectionInformation) {
       this.redirectionInformation = redirectionInformation;
       this.isRedirectionInformation = true;
    }
    /** Indicates if the Redirection Information optional parameter is present.
      * @return True when present, false otherwise.  */
    public boolean isRedirectionInformationPresent() {
        return isRedirectionInformation;
    }
    /** Gets Route List.  */
    public RouteList getRouteList() throws ParameterNotSetException {
        if (isRouteList)
            return routeList;
        throw new ParameterNotSetException("Route List: not set.");
    }
    /** Sets Route List.  */
    public void setRouteList(RouteList routeList) {
        this.routeList = routeList;
        this.isRouteList = true;
    }
    /** Indicates if the Route List optional parameter is present.
      * @return True when present, false otherwise.  */
    public boolean isRouteListPresent() {
        return isRouteList;
    }
    /** Gets Travelling Class Mark.  */
    public LocationNumber getTravellingClassMark() throws ParameterNotSetException {
        if (isTravellingClassMark)
            return travellingClassMark;
        throw new ParameterNotSetException("Travelling Class Mark: not set.");
    }
    /** Sets Travelling Class Mark.  */
    public void setTravellingClassMark(LocationNumber travellingClassMark) {
        this.travellingClassMark = travellingClassMark;
        this.isTravellingClassMark = true;
    }
    /** Indicates if the Travelling Class Mark optional parameter is present.
      * @return True when present, false otherwise.  */
    public boolean isTravellingClassMarkPresent() {
        return isTravellingClassMark;
    }
    /** Gets Extensions Parameter.  */
    public ExtensionField[] getExtensions() throws ParameterNotSetException {
        if (isExtensions)
            return extensions;
        throw new ParameterNotSetException("Extensions: not set.");
    }
    /** Gets a particular Extension Parameter.  */
    public ExtensionField getExtension(int index) {
        return extensions[index];
    }
    /** Sets Extensions Parameter.  */
    public void setExtensions(ExtensionField extensions[]) {
        this.extensions = extensions;
        this.isExtensions = true;
    }
    /** Sets a particular Extensions Parameter.  */
    public void setExtension(int index, ExtensionField extension) {
        this.extensions[index] = extension;
    }
    /** Indicates if the Extensions optional parameter is present.
      * @return True when present, false otherwise.  */
    public boolean isExtensionsPresent() {
        return isExtensions;
    }
    private DPSpecificCommonParameters dPSpecificCommonParameters;
    private java.lang.String calledPartyBusinessGroupID;
    private boolean isCalledPartyBusinessGroupID = false;
    private CalledPartySubaddress calledPartySubaddress;
    private boolean isCalledPartySubaddress = false;
    private java.lang.String callingPartyBusinessGroupID;
    private boolean isCallingPartyBusinessGroupID = false;
    private CallingPartySubaddress callingPartySubaddress;
    private boolean isCallingPartySubaddress = false;
    private OriginalCalledPartyID originalCalledPartyID;
    private boolean isOriginalCalledPartyID = false;
    private RedirectingPartyID redirectingPartyID;
    private boolean isRedirectingPartyID = false;
    private RedirectionInformation redirectionInformation;
    private boolean isRedirectionInformation= false;
    private RouteList routeList;
    private boolean isRouteList = false;
    private LocationNumber travellingClassMark;
    private boolean isTravellingClassMark = false;
    private ExtensionField extensions[];
    private boolean isExtensions = false;
}

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
