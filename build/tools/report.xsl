<?xml version='1.0'?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:template match="*/TestSuite">
    <p/>
    <table align="center" width="90%">
      <tr>
 	<td colspan="2" bgcolor="#f0f0f0"><div align="center"><xsl:value-of select="@name" /></div></td>
      </tr>
      <tr>
 	<td bgcolor="#f0f0e0" width="25%">Result</td>
	<xsl:if test="@result='passed'">
	  <td bgcolor="#30e050" width="75%"><xsl:value-of select="@result" /></td>
	</xsl:if>
	<xsl:if test="@result='failed'">
	  <td bgcolor="#f03020" width="75%"><xsl:value-of select="@result" /></td>
	</xsl:if>
      </tr>
      <tr>
 	<td bgcolor="#f0f0e0" width="25%">Assertions Passed</td>
	<xsl:if test="@assertions_passed='0'">
	  <td bgcolor="#f03020" width="75%"><xsl:value-of select="@assertions_passed" /></td>
	</xsl:if>
	<xsl:if test="@assertions_passed!='0'">
	  <td bgcolor="#30e050" width="75%"><xsl:value-of select="@assertions_passed" /></td>
	</xsl:if>
      </tr>
      <tr>
 	<td bgcolor="#f0f0e0" width="25%">Assertions Failed</td>
	<xsl:if test="@assertions_failed='0'">
	  <td bgcolor="#30e050" width="75%"><xsl:value-of select="@assertions_failed" /></td>
	</xsl:if>
	<xsl:if test="@assertions_failed!='0'">
	  <td bgcolor="#f03020" width="75%"><xsl:value-of select="@assertions_failed" /></td>
	</xsl:if>
      </tr>
      <tr>
 	<td bgcolor="#f0f0e0" width="25%">Expected Failures</td>
	<xsl:if test="@expected_failures='0'">
	  <td bgcolor="#30e050" width="75%"><xsl:value-of select="@expected_failures" /></td>
	</xsl:if>
	<xsl:if test="@expected_failures!='0'">
	  <td bgcolor="#f03020" width="75%"><xsl:value-of select="@expected_failures" /></td>
	</xsl:if>
      </tr>
      <tr>
 	<td bgcolor="#f0f0e0" width="25%">Test cases Passed</td>
	<xsl:if test="@test_cases_passed='0'">
	  <td bgcolor="#f03020" width="75%"><xsl:value-of select="@test_cases_passed" /></td>
	</xsl:if>
	<xsl:if test="@test_cases_passed!='0'">
	  <td bgcolor="#30e050" width="75%"><xsl:value-of select="@test_cases_passed" /></td>
	</xsl:if>
      </tr>
      <tr>
 	<td bgcolor="#f0f0e0" width="25%">Test cases Failed</td>
	<xsl:if test="@test_cases_failed='0'">
	  <td bgcolor="#30e050" width="75%"><xsl:value-of select="@test_cases_failed" /></td>
	</xsl:if>
	<xsl:if test="@test_cases_failed!='0'">
	  <td bgcolor="#f03020" width="75%"><xsl:value-of select="@test_cases_failed" /></td>
	</xsl:if>
      </tr>
      <tr>
 	<td bgcolor="#f0f0e0" width="25%">Test cases Skipped</td>
	<xsl:if test="@test_cases_skipped='0'">
	  <td bgcolor="#30e050" width="75%"><xsl:value-of select="@test_cases_skipped" /></td>
	</xsl:if>
	<xsl:if test="@test_cases_skipped!='0'">
	  <td bgcolor="#f03020" width="75%"><xsl:value-of select="@test_cases_skipped" /></td>
	</xsl:if>
      </tr>
      <tr>
 	<td bgcolor="#f0f0e0" width="25%">Test cases Aborted</td>
	<xsl:if test="@test_cases_aborted='0'">
	  <td bgcolor="#30e050" width="75%"><xsl:value-of select="@test_cases_aborted" /></td>
	</xsl:if>
	<xsl:if test="@test_cases_aborted!='0'">
	  <td bgcolor="#f03020" width="75%"><xsl:value-of select="@test_cases_aborted" /></td>
	</xsl:if>
      </tr>
    </table>
  </xsl:template>
  
  <xsl:template match="TestResult">
    <html>
      <head>
	<title> Boost::Unittest Report. </title>
      </head>
      
      <body bgcolor="e0e0f0">
	<div align="center">
	  <h3> <b> Unittest Report </b> </h3>
	</div>	

	<xsl:apply-templates/>
      </body>
    </html>
  </xsl:template>
  
</xsl:stylesheet>
