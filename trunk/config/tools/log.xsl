<?xml version='1.0'?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  
  <xsl:template name="testcase">

    <h3>TestCase <xsl:value-of select="@name"/></h3>
    <table align="center" width="90%">
      <tr>
	<th with="25%" bgcolor="#afa">File</th>
	<th with="15%"  bgcolor="#afa">Line#</th>
	<th with="60%"  bgcolor="#afa">Message</th>
      </tr>
	  
      <xsl:for-each select="Error">
	<tr>
	  <td bgcolor="#f00"><xsl:value-of select="@file"/></td>
	  <td bgcolor="#f00"><xsl:value-of select="@line"/></td>
	  <td bgcolor="#f00"><xsl:value-of select="."/></td>
	</tr>
      </xsl:for-each>
      <xsl:for-each select="Info">
	<tr>
	  <td bgcolor="#0f0"><xsl:value-of select="@file"/></td>
	  <td bgcolor="#0f0"><xsl:value-of select="@line"/></td>
	  <td bgcolor="#0f0"><xsl:value-of select="."/></td>
	</tr>
      </xsl:for-each>
      <tr>
	<td colspan="3" bgcolor="#88f">Teting Time : <xsl:value-of select="TestingTime"/> ms</td>
      </tr>
      
    </table>

  </xsl:template>
  
  <xsl:template name="testsuite">
    <h2>TestSuite <xsl:value-of select="@name"/></h2>
    <xsl:for-each select="TestSuite">
      <xsl:call-template name="testsuite"/>
    </xsl:for-each>
    <xsl:for-each select="TestCase">
      <xsl:call-template name="testcase"/>
    </xsl:for-each>
  </xsl:template>
  
  <xsl:template match="TestLog/TestSuite">
    <html>
      <head>
	<title> Boost::Unittest Log. </title>
      </head>

      <body bgcolor="e0f0f0">
	<div align="center">
	  <h1> <b> Unittest Log</b> </h1>
	</div>	
	<xsl:for-each select="TestSuite">
	  <xsl:call-template name="testsuite"/>
	</xsl:for-each>
      </body>
    </html>
    
  </xsl:template>
</xsl:stylesheet>
