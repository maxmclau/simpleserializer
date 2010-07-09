<?xml version='1.0'?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text"/>

<xsl:template name="testcase">
Running   TestCase <xsl:value-of select="@name"/>.
<xsl:for-each select="Error">
<xsl:value-of select="@file"/>:<xsl:value-of select="@line"/>: error: <xsl:value-of select="."/>.
</xsl:for-each>
<xsl:for-each select="Info">
<xsl:value-of select="@file"/>:<xsl:value-of select="@line"/>: warning: <xsl:value-of select="."/>.
</xsl:for-each>Teting Time : <xsl:value-of select="TestingTime"/> ms
</xsl:template>
  
<xsl:template name="testsuite">
Running TestSuite <xsl:value-of select="@name"/>
<xsl:for-each select="TestSuite">
<xsl:call-template name="testsuite"/>
</xsl:for-each>
<xsl:for-each select="TestCase">
<xsl:call-template name="testcase"/>
</xsl:for-each>
</xsl:template>


<xsl:template match="TestLog">
<xsl:for-each select="TestSuite">
<xsl:call-template name="testsuite"/>
</xsl:for-each>
</xsl:template>
</xsl:stylesheet>
