---
layout: template
title: The FRC Team
---
<h2>Members</h2>
<table>
{% for d in site.data.frc-members %}
<tr>
<td>
  {% if d.name != null%}
  {% if d.file != null %}
  <img src="{{ site.url }}/assets/img/stryke-force/students-frc/{{ d.file }}" width="200px">
  {% else %}
  <img src="{{ site.url }}/assets/img/sf-logo.jpg" width="200px">
  {% endif %}
  </td>
  <td>&nbsp;&nbsp;&nbsp;</td>
<td>
  <h4>{{ d.name }} {% if d.grade != null %} – {{ d.grade }}{% endif %}</h4>
  {% if d.school != null %}
  <p>{{ d.school }}</p>
  {% endif %}
  {% if d.job != null %}
  <p>{{ d.job }} Team</p>
  {% endif %}
</td>
  {% endif %}

  </tr>
{% endfor %}
</table>
