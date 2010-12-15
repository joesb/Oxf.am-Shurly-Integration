// $Id: README.txt $

This module integrates a Drupal website with the Oxf.am short URL service
provided by the ShURLy module (http://drupal.org/project/shurly).

This module does several things.

+++ USAGE +++
1. Place the module in your modules directory and enable.
2. Visit admin/user/permissions to set up permissions (see below).
3. Visit admin/settings/oxfam-shurly to administer integration with oxf.am 
(see below).
4. Optionally, this module includes 2 themeable blocks you may choose to use.
  a) a Permalink short URL text string
  b) a 'Tweet this' icon.

+++ HOW IT WORKS +++
Oxf.am includes a web service for shortening URLs. This module integrates with
that service to retrieve shortened URLs when a node is created or updated on
your site. It does this using the aliased URL of the node page. If your node
changes its alias during an update, this module checks and updates to a new
short URL automatically.

+++ ADMINISTRATION +++
admin/settings/oxfam-shurly offers several adminstration tools.

Choose whether to make short URLs with the oxf.am short URL service.

Set a general oxf.am API key so that URLs generated on your site are
associated with your main oxf.am account. This is used if the user creating
the short URL does not have their own oxf.am API key (see below).

Choose which web service to use for retrieving short URLs from oxf.am. If your
site is using PHP 5.2.0 or greater, you will be able to use the JSON service,
which is the optimal method. If your PHP version is less that 5.2.0, please
choose an alternative web service.

You can also select the node types for which short URLs are automatically
generated.

+++ PERMISSIONS +++
This module gives one new permission - add own oxf.am account - that allows
users with that permission to add an Oxf.am API key to their user account.
This allows any short URLs generated on your site to be associated with their
oxf.am account.

+++ BLOCKS +++
This module includes two blocks. The content of both blocks are themable.

'Oxf.am: Node permalink' just displays a string of text with the short URL as
a permalink. You can theme this block content by overriding 
theme_shurly_permalink().

'Oxf.am: Tweet this' displays a 'Tweet this!' icon with the short URL sent to
Twitter as part of the 'status' query string. You can theme this block content
by overriding theme_shurly_tweet_this().
